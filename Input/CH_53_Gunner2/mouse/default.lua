local cockpit = folder.."../../../Cockpit/Scripts/"
dofile(cockpit.."devices.lua")
dofile(cockpit.."command_defs.lua")

return {

keyCommands = {
{combos = {{key = 'MOUSE_BTN1'}}, down = iCommandPlaneFire, up = iCommandPlaneFire, value_down = 1, value_up = 0, name = _('Machinegun fire'), category = _('Weapon')},
{combos = {{key = 'MOUSE_BTN2'}}, down = iCommand_ExplorationStart, name = _('Enable visual recon mode'), category = _('View Cockpit')},
{combos = {{key = 'MOUSE_BTN3'}}, down = iCommandViewTransposeModeOn, up = iCommandViewTransposeModeOff, name = _('Camera transpose mode (press and hold)'), category = _('View Cockpit')},
},

axisCommands = {

-- mouse axes
--{combos = {{key = 'MOUSE_X'}}, action = iCommandPlaneViewHorizontal, name = _('Camera Horizontal View')},
--{combos = {{key = 'MOUSE_Y'}}, action = iCommandPlaneViewVertical, name = _('Camera Vertical View')},
{combos = {{key = 'MOUSE_Z'}}, action = iCommandPlaneZoomView, name = _('Camera Zoom View')},
                          
						  
{action = device_commands.Button_89, cockpit_device_id = devices.WEAPON_SYS, name = _('Gun Left/Right')},
{action = device_commands.Button_88, cockpit_device_id = devices.WEAPON_SYS, name = _('Gun Up/Down')},

{combos = {{key = 'MOUSE_X'}}, action = device_commands.Button_94, cockpit_device_id = devices.WEAPON_SYS, name = _('Camera Horizontal View')},
{combos = {{key = 'MOUSE_Y'}}, action = device_commands.Button_95, cockpit_device_id = devices.WEAPON_SYS, name = _('Camera Vertical View')},

},
}
