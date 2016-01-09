-- Keyset file for Lawyer Race

--  keysets

useVimkeys = false

function getControls(numOfPlayers, player, controllers)
  lwr.debug("getControls(" .. numOfPlayers .. ", " .. player .. ", " .. controllers .. ")")
  controls = {}
  controls[1] = {}
  controls[2] = {}
  controls[3] = {}
  controls[4] = {}
  
  controllerControls = {
      up = {"controller_up"},
      left = {"controller_left"},
      down = {"controller_down"},
      right = {"controller_right"},
      stop = {"controller_a"}
  }
  
  keyControls = {}
  if useVimkeys and numOfPlayers == 1 then
    lwr.debug("Using vimkeys!")
    keyControls[1] = {
      up = {"k"},
      left = {"h"},
      down = {"j"},
      right = {"l"},
      stop = {"space"}
    }
  else
    keyControls[1] = {
      up = {"up"},
      left = {"left"},
      down = {"down"},
      right = {"right"},
      stop = {"rctrl"}
    }
  end
  keyControls[2] = {
    up = {"w"},
    left = {"a"},
    down = {"s"},
    right = {"d"},
    stop = {"lctrl"}
  }
  keyControls[3] = {
    up = {"i"},
    left = {"j"},
    down = {"k"},
    right = {"l"},
    stop = {"space"}
  }
  keyControls[4] = {
    up = {"num_8"},
    left = {"num_4"},
    down = {"num_5"},
    right = {"num_6"},
    stop = {"num_0"}
  }
  
  if numOfPlayers == 1 then
    lwr.debug("both controller and keyboard accepted")
    controls[1] = keyControls[1]
    controls[1]["stop"][1] = "space"
    --accept both controller and keyboard
    controls[1]["up"][2] = "controller_up"
    controls[1]["left"][2] = "controller_left"
    controls[1]["down"][2] = "controller_down"
    controls[1]["right"][2] = "controller_right"
    controls[1]["stop"][2] = "controller_a"
  elseif numOfPlayers > 1 then
    for i=1,controllers do
      controls[i] = controllerControls
    end
    for i=controllers+1,4 do
      controls[i] = keyControls[i - controllers]
    end
  end
  
  if numOfPlayers > 1 and numOfPlayers - controllers == 1 then
    controls[controllers + 1]["stop"] = {"space"} -- exception
  end

  lwr.debug("Returning controls for player " .. player)
  return controls[player]
end


--[[
Available keys:
a-z
0-9
up
down
left
right 
num_0 - num_9
rctrl 
lctrl 
rshift
lshift
lalt
altgr
tab 
insert
delete
home
end 
pgup
pgdown
backspace
return
space
]]--
