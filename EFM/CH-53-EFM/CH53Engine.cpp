#include "CH53.h"

namespace CH53
{
	Engine::Engine()
		: throttleInput(0)
		, N1_RPM(0)
		, N2_RPM(0)
		, engineRunning(false)
		, isStarterPressed(false)
		, oilPressure(0)
		, turbineTemperature(20)
		, hotStart(false)
		, engineFire(false)
		, torque(0)
		, rotorPosition(0)
	{
	}

	Engine::~Engine()
	{
	}

	void Engine::vInit(bool hotStart, bool inAir)
	{
		if (hotStart)
		{
			throttleInput = 1;
			N1_RPM = 100;
			N2_RPM = 100;
			isStarterPressed = false;
			engineRunning = true;
			rotorPosition = 0;
			turbineTemperature = 600;
			hotStart = false;
			engineFire = false;
		}
		else
		{
			throttleInput = 0;
			N1_RPM = 0;
			N2_RPM = 0;
			isStarterPressed = false;
			engineRunning = false;
			rotorPosition = 0;
			turbineTemperature = 15;
			hotStart = false;
			engineFire = false;
		}
	}

	void Engine::setThrottleInput(const double value)
	{
		throttleInput = value;
		throttleInput = limit(throttleInput, 0, 1);
	}
	void Engine::setStarterButton(const float value)
	{
		if (value == 1)
		{
			isStarterPressed = true;
			return;
		}
		isStarterPressed = false;
	}

	double Engine::getCoreRPM() const
	{
		return N1_RPM;
	}

	double Engine::getCoreRelatedRPM() const 
	{
		return N1_RPM / 100;
	}

	double Engine::getTurbineRPM() const
	{
		return N2_RPM;
	}

	double Engine::getTurbineRelatedRPM() const
	{
		return N2_RPM / 100;
	}

	void Engine::spinRotor(const double dt)
	{
		rotorPosition += (N2_RPM /100) * dt; 
		if (rotorPosition > 1)
		{
			rotorPosition = 0;
		}
	}
	void Engine::turnStarter(double dt)
	{
		N1_RPM += dt * 3; // will get to 15% in 5 seconds
		N1_RPM = limit(N1_RPM, 0, 20); // starter wont turn engine past 20% or so
	}
	void Engine::spoolUp(double dt)
	{
		N1_RPM += dt * 3.4; 
		N1_RPM = limit(N1_RPM, 0, 62);
	}
	void Engine::spoolDown(double dt)
	{
		N1_RPM -= dt * 5;
		N1_RPM = limit(N1_RPM, 0, 101);
	}
	void Engine::updateTOT(double dt, bool isFuelFlow, double ambientTemperature_DegC)
	{
		double TOTtarget;
		if (turbineTemperature > ambientTemperature_DegC && isFuelFlow == false)
		{
			if (N1_RPM > 1) // engine isn't ignited but still turning, causing air to move and cool engine faster
			{
				if (turbineTemperature > 260)
				{
					turbineTemperature -= (turbineTemperature - ambientTemperature_DegC) * dt * 0.08;
				}
				else
				{
					turbineTemperature -= dt * 5.2;
				}
			}
			else // engine cooling off due to lower ambient air
			{
				turbineTemperature -= dt * 1.7;
			}
		}
		else if (isFuelFlow == true)
		{
			if (N1_RPM < 58) // starting
			{
				if (N1_RPM < 32)
				{
					TOTtarget = 730;
					if (hotStart == true)
					{
						TOTtarget = 1200;
					}
					turbineTemperature += (TOTtarget - turbineTemperature) * dt;
				}
				else if (N1_RPM > 37) // temp will stay high for a short period of time before decending
				{
					turbineTemperature -= dt * 4;
				}
			}
			else // running
			{
				TOTtarget = (N1_RPM - 58) / 0.42 + 550; // linear 550-650 for now
				if (turbineTemperature > TOTtarget)
				{
					turbineTemperature -= dt * 4;
				}
				else 
				{
					turbineTemperature += dt * 4;
				}
			}
		}
		turbineTemperature = limit(turbineTemperature, 0, 1200);

		if (turbineTemperature > 1000) //1000
		{
			engineFire = true;
		}
	}
	//
	//	Gets the total power available from all engines (MAX or current)
	//  allows for 1 or more engines to under perform or be off completely
	//  Input -1=MAX power  0=current power 
	//  Output total power in KWatts

	double Engine::getEnginePowerTotal(int current_or_max) {
		double pwr = 0;
		if (current_or_max == -1) { //MAX
			for (int i = 0; i < number_of_engines; i++) {
				pwr += engine_max_power[i];
			}
		}
		else if (current_or_max == 0) { //current
			for (int i = 0; i < number_of_engines; i++) {
				pwr += engine_current_power[i];
			}
		}
		
		return pwr;
	}
	double Engine::getEnginePowerAvg(int current_or_max) {
		double pwr = 0;
		if (current_or_max == -1) { //MAX
			for (int i = 0; i < number_of_engines; i++) {
				pwr += engine_max_power[i];
			}
			pwr = pwr / number_of_engines;
		}
		else if (current_or_max == 0) { //current
			for (int i = 0; i < number_of_engines; i++) {
				pwr += engine_current_power[i];
			}
			pwr = pwr / number_of_engines;
		}

		return pwr;
	}

	double Engine::LagrangeInterpolate(LagrangeData function[], int xi, int n) {
		double result = 0;
		for (int i = 0; i < n; i++) {
			double term = function[i].y;
			for (int j = 0; j < n; j++) {
				if (j != i) {
					term = term * (xi - function[j].x) / double(function[i].x - function[j].x);
				}
			}
			result += term;
		}
		return result;
	}

	void Engine::updateTorque(double dt, double collective)
	{
		// Natops diagram 22-5
		// Nr  100% : Torque = (Horsepower/100) * 3.3
		
		// torque available
		double Q_available;
		Q_available = ((throttleInput * (getEnginePowerTotal(0) * 1.35962)) / 100) * 3.3;	// table is in SHP 1.35962 is KW to shp conversion.output is percent, so it's all good

		// as I increase the collective, the pwr required to maintain 100% rpm increases

		//  1 in/hg =  33.86389 hpa
		// PA (ft) = ( 29.92 - AltSet.(in/hg) ) * 1000 + FieldElev.(ft)   eg.  Pressure Altitude = (((1013 /  33.86389) - (1018/ 33.86389)) * 1000) + 100 (ft asl) = -47ft
		// DA (ft) = PresAlt.(ft) + 118.8 * ( OAT(°C) - ISA(°C) )  eg. -47ft + (118.8 * (20 - 14.8)) = 570.76 ft

		// torque_required from chart
		//LagrangeData function[] = { {0,66}, {10,102}, {20,148}}; // Natops 23-2 hover at 10 ft  DA=8000 ft, weight=65000lbs  torque should be 96%
		//double torque_required = LagrangeInterpolate(function, 8, 3);

		// torque from 'rough' calculation
		// Q_max: if the collective is pulled all the way up and the blades are at max angle.
		double Q_max = (CH53::MainRotor::blade_pitch_max / 10000)
			* 0.5 * 1.225
			* (3.14159 * (CH53::MainRotor::rotor_blade_length * CH53::MainRotor::rotor_blade_length))
			* ((getCoreRelatedRPM() * Engine::rpm_100_percent * 0.1047198 * CH53::MainRotor::rotor_blade_length) * (getCoreRelatedRPM() * Engine::rpm_100_percent * 0.1047198 * CH53::MainRotor::rotor_blade_length))
			* CH53::MainRotor::rotor_blade_length;	// in Newton meters

		//double x=(systems.blade_pitch_max /20000)* 0.5 * 1.225 * (3.14159 * (12.03 * 12.03))* ((1.09 * 185 * 0.1047198 * 12.03) * (1.09 * 185 * 0.1047198 * 12.03)) * 12.03;

		//  (blade_pitch_angle / 10000) is a fudge.. it should be from a curve: https://aviation.stackexchange.com/questions/49167/what-is-the-relationship-between-speed-torque-and-pitch-in-a-helicopter/67197#67197

		double blade_pitch_angle = systems.MainRotor.getCollectivePitch();
		double Q = (blade_pitch_angle / 10000) 
			* 0.5 * 1.225 
			* (3.14159 * (CH53::MainRotor::rotor_blade_length * CH53::MainRotor::rotor_blade_length)) 
			* ((getCoreRelatedRPM() * Engine::rpm_100_percent * 0.1047198 * CH53::MainRotor::rotor_blade_length) * (getCoreRelatedRPM() * Engine::rpm_100_percent * 0.1047198 * CH53::MainRotor::rotor_blade_length))
			* CH53::MainRotor::rotor_blade_length; // in Newton meters

		double power_reqd = Q * (getCoreRelatedRPM() * Engine::rpm_100_percent * 0.1047198); // torque * RPM (in rad/s)
		double power_available = getEnginePowerTotal(0) * 1000;

		if (power_reqd > power_available) {
			// theres a problem.
			// engine is being over torqed?
			// too long and bad things happen
			// the govenor is asking the engine to increase power to keep its rotor at 185 RPM
			// if it cant then RPM will decrease til power_reqd=power_available !?
			N2_RPM--;
		}
		
		torque = (Q / Q_max) * 100; // torque as a percent of total torque (total torque is when blade is at 23 deg)

		// 
		//double power_available = throttleInput * getEnginePowerTotal(0); //  kWatts

		// 
		// 
		// 
		// 1 shp = 745.7 watts
		// 1 rpm = 0.104 rad/s
		// 1 lb = 0.454 kg
		// 
		// throttle=125% ->3925 shp = 2926872  Watts
		// throttle=100% ->3140 shp = 2341498  Watts
		// 185 RPM = 19.37 Rad/s  
		// 231 RPM =  24.19  rad/s
		// Rotor Area =  460 sqm
		// 
		// torque = Watts/(rad/s)
		// 
		// flat chat (30 min max)
		// N2_RPM = 125% then torque should be -> 2926872/24.19 = 120995 Newton-meters  (max 30 min running)  SO..this is max available torque?
		// so the engine is working at FULL capacity to deliver this torque  (ie. to lift this weight at this density-altitude)
		//
		//// so at N2_RPM = 100%  then torque should be -> (2926872/1.25)/19.37 = 120882 Newton-meters  (normal continuous running)

		// Power Loading [PL] = Power/Area  = 2926872/470 = 6362.7
		// Thrust Loading[TL] = 8.6859 * PL^(-0.3107) = 0.572537
		// Lift = TL * power = 0.572537 * 2926872 = 1677097
		// 
		// Sooo... if I want to hover with 42000 lbs  (19068  kg) (186866.4 newtons) I have enuf with the engine running 
		// 
		// set throttle to 100% (3140 shp)(max torq available= , pull collective, torq increases, if 
		//torque = ((N2_RPM-70)/.39) * systems.torq_in_ground_effect_hover_empty; // just linear based on N2
	}

	void Engine::vSimulate(struct Systems& systems, EDPARAM& cockpitAPI, double dt)
	{
		if (N1_RPM >= 58 && systems.Fuel.isFuelFlow)
		{
			engineRunning = true;
		}
		else
		{
			engineRunning = false;
		}

		if (isStarterPressed && systems.Electrics.isDC_busPowered)
		{
			if (systems.Fuel.isFuelFlow == true && N1_RPM > 13)
			{
				spoolUp(dt);
			}
			else
			{
				turnStarter(dt);
			}
		}
		else if (N1_RPM > 58 && N1_RPM < 62 && engineRunning)
		{
			spoolUp(dt);
		}
		else if (engineRunning == false)
		{
			spoolDown(dt * 0.2); //attempt at autorotate // original:   spoolDown(dt);
		}
		
		if (engineRunning && N1_RPM >= 62)  // so if N1 gets to 62..it can never fall below 62 unless the engine is killed?
		{
			N1_RPM = (39 * throttleInput) + 62;
			N1_RPM = limit(N1_RPM, 0, 101);
		}


		// N2 will try to reach the rpm of 15-90%N1 for 0-100%N2 
		// this will allow the rotor to start moving at 15%N1
		double targetRPM = 0;
		targetRPM = (N1_RPM - 15) / 0.75;
		targetRPM = limit(targetRPM, 0, 109);
		double growthRate = 0;
		if ((targetRPM - N2_RPM) > 40.0)
		{
			growthRate = 0.4 * 40;
		}
		else
		{
			growthRate = 0.4 * (targetRPM - N2_RPM);
		}
		N2_RPM += (growthRate * dt);
		N2_RPM = limit(N2_RPM, 0.0, 109.0);
		


		spinRotor(dt);
		updateTOT(dt, systems.Fuel.isFuelFlow, systems.Motion.ambientTemperature_DegC);
		updateTorque(dt, systems.AFCS.getCollectiveControl());



		void* N2RPM = cockpitAPI.getParamHandle("N2_RPM"); // for use in digital gauge
		if (N2RPM != nullptr)
		{
			cockpitAPI.setParamNumber(N2RPM, N2_RPM);
		}

		void* TOT = cockpitAPI.getParamHandle("TOT"); // for use in digital gauge
		if (TOT != nullptr)
		{
			cockpitAPI.setParamNumber(TOT, turbineTemperature);
		}

		void* TRQ = cockpitAPI.getParamHandle("TRQ"); // for use in digital gauge
		if (TRQ != nullptr)
		{
			cockpitAPI.setParamNumber(TRQ, torque);
		}
	}
};
