CH_53 = { 
	--center_of_mass		= {0.0, -0.274, 0},	--x,y,z {0.0, -0.274, 0}
	--center_of_mass		= {0.0, 0.674, 0},
	--center_of_mass		= {0.0, 1.174, 0},
	center_of_mass		= {0.0, 2.174, 0},
	--moment_of_inertia = {198000,	33176162,	80778}, --{6170,	28982,	33441}, --{198000,	76162,	80778}, 
	--moment_of_inertia = {126395,  308559, 192377}, 
	--moment_of_inertia = {126395,  608559, 192377}, -- TESTED
	--moment_of_inertia = {226395,  1308559, 692377},
	moment_of_inertia = {426395,  3308559, 692377},

	suspension =
	{	
		{--Nose wheel
			mass = 30,
			 --pos   			  = {5.312, 0.102,    0}
			damage_element = 0, 
			self_attitude = true,
			wheel_axle_offset = 0.14,
			yaw_limit = math.rad(55.0),
			damper_coeff = 400.0, 
			allowable_hard_contact_length	= 0.59,				

			  amortizer_max_length     = 0.43,
			  amortizer_basic_length     = 0.43,
			  amortizer_spring_force_factor   = 990000.0, -- force = spring_force_factor * pow(reduce_length, amortizer_spring_force_factor_rate
			  amortizer_spring_force_factor_rate  = 1,
			  amortizer_static_force     = 47500.0,
			  amortizer_reduce_length     = 0.43, --0.43
			  amortizer_direct_damper_force_factor = 50000,
			  amortizer_back_damper_force_factor  = 60000,

			  anti_skid_installed = true,

			  wheel_radius      = 0.17,
			  wheel_static_friction_factor  = 0.75 ,
			  -- wheel_side_friction_factor    = 0.85,--0.85 ,
			  wheel_roll_friction_factor    = 0.08 ,
			  wheel_glide_friction_factor   = 0.65 ,
			  wheel_damage_force_factor     = 1450.0,
			  
				wheel_moment_of_inertia   = 0.15, --wheel moi as rotation body

				wheel_brake_moment_max = 29000.0, -- maximum value of braking moment  , N*m 
				
				arg_post			  = 0,
				arg_amortizer		  = 2,
				arg_wheel_rotation    = 76,
				arg_wheel_yaw		  = 1,
				collision_shell_name  = "WHEEL_F",
				 arg_wheel_damage   = 134,
			},
			{--Left wheel
				mass = 80,
				 --pos   			  = {-2.371, -0.071, 1.808},
				damage_element	    = 3,
				wheel_axle_offset 	= 0.38,
				self_attitude	    = false,
				yaw_limit		    = math.rad(0.0),
				damper_coeff	    = 160.0,
				
				 amortizer_max_length     = 0.43,
			  amortizer_basic_length     = 0.43,
			  amortizer_spring_force_factor   = 990000.0, -- force = spring_force_factor * pow(reduce_length, amortizer_spring_force_factor_rate
			  amortizer_spring_force_factor_rate  = 1,
			  amortizer_static_force     = 47500.0,
			  amortizer_reduce_length     = 0.43, --0.43
			  amortizer_direct_damper_force_factor = 50000,
			  amortizer_back_damper_force_factor  = 60000,
				  
				--   amortizer_direct_damper_force_factor = 50000,
				--   amortizer_back_damper_force_factor  = 60000,

				allowable_hard_contact_length			= 0.55,
				anti_skid_installed = false,
				--wheel_roll_friction_factor     = 0.20,-- DO NOT activate, already implemented in EFM code
				wheel_damage_speed			   = 180,
				wheel_moment_of_inertia  	   = 0.6, --wheel moi as rotation body
				
				
				 wheel_radius     				= 0.372,
				  wheel_static_friction_factor  = 0.75 ,
				  wheel_side_friction_factor    = 0.85,--0.85 ,
				  wheel_roll_friction_factor    = 0.08 ,
				  wheel_glide_friction_factor   = 0.65 ,
				  wheel_damage_force_factor     = 1450.0,
				  
				wheel_brake_moment_max 			= 29000, -- maximum value of braking moment  , N*m 
				
				arg_post			  = 5,
				arg_amortizer		  = 6,
				arg_wheel_rotation    = 77,
				arg_wheel_yaw		  = -1,
				collision_shell_name  = "WHEEL_L",
				arg_wheel_damage   = 136
			},
			{-- Right wheel
				mass = 80,
				 --pos   			  = {-2.371, -0.071, -1.808},
				damage_element	    = 3,
				wheel_axle_offset 	= 0.38,
				self_attitude	    = false,
				yaw_limit		    = math.rad(0.0),
				damper_coeff	    = 160.0,
				
				 amortizer_max_length     = 0.43,
			  amortizer_basic_length     = 0.43,
			  amortizer_spring_force_factor   = 990000.0, -- force = spring_force_factor * pow(reduce_length, amortizer_spring_force_factor_rate
			  amortizer_spring_force_factor_rate  = 1,
			  amortizer_static_force     = 47500.0,
			  amortizer_reduce_length     = 0.43, --0.43
			  amortizer_direct_damper_force_factor = 50000,
			  amortizer_back_damper_force_factor  = 60000,
				  
				--   amortizer_direct_damper_force_factor = 50000,
				--   amortizer_back_damper_force_factor  = 60000,

				allowable_hard_contact_length			= 0.55,
				anti_skid_installed = false,
				--wheel_roll_friction_factor     = 0.20,-- DO NOT activate, already implemented in EFM code
				wheel_damage_speed			   = 180,
				wheel_moment_of_inertia  	   = 0.6, --wheel moi as rotation body
				
				 wheel_radius     				= 0.372,
				  wheel_static_friction_factor  = 0.75 ,
				  wheel_side_friction_factor    = 0.85,--0.85 ,
				  wheel_roll_friction_factor    = 0.08 ,
				  wheel_glide_friction_factor   = 0.65 ,
				  wheel_damage_force_factor     = 1450.0,
				  
				wheel_brake_moment_max 			= 29000, -- maximum value of braking moment  , N*m 
				
				
				arg_post			  = 3,
				arg_amortizer		  = 4,
				arg_wheel_rotation    = 77,
				arg_wheel_yaw		  = -1,
				collision_shell_name  = "WHEEL_R",
							
			},
	},
	-- gear posts initialization
	
	disable_built_in_oxygen_system	= false,
	--[[ ------------------------------------------------------------- ]]--
	-- END -- this part of the file is not intended for an end-user editing

	-- view shake amplitude
	minor_shake_ampl = 0.21,
	major_shake_ampl = 0.5,

	-- debug
	debugLine = "{M}:%1.3f {IAS}:%4.1f {AoA}:%2.1f {ny}:%2.1f {nx}:%1.2f {AoS}:%2.1f {mass}:%2.1f {Fy}:%2.1f {Fx}:%2.1f {wx}:%.1f {wy}:%.1f {wz}:%.1f {Vy}:%2.1f {dPsi}:%2.1f",
	record_enabled = false,
}