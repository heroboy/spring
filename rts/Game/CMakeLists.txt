
# This list was created using this *nix shell command:
# > find . -name "*.cpp" | sort
SET(sources_engine_Game_common
		"${CMAKE_CURRENT_SOURCE_DIR}/Action.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/AviVideoCapturing.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Benchmark.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Camera/CameraController.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Camera/FPSController.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Camera/FreeController.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Camera/OrbitController.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Camera/OverheadController.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Camera/OverviewController.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Camera/RotOverheadController.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Camera/SmoothController.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Camera/TWController.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/CameraHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/ChatMessage.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/ClientSetup.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/CommandMessage.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Console.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/ConsoleHistory.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/DummyVideoCapturing.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/FPSUnitController.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/GameController.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/GameData.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/GameHelper.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/GameServer.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/GameSetup.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/GameVersion.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/GlobalUnsynced.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/IVideoCapturing.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/InMapDraw.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/InMapDrawModel.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/LoadScreen.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Messages.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/NetCommands.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Player.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/PlayerBase.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/PlayerHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/PlayerRoster.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/PlayerRosterDrawer.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/PlayerStatistics.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/PreGame.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SelectedUnits.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SelectedUnitsAI.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/SyncedGameCommands.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/TraceRay.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/TeamController.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/CommandColors.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/CursorIcons.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/EndGameBox.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/GameInfo.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/GameSetupDrawer.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/GuiHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/HwMouseCursor.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/InfoConsole.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/InputReceiver.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/KeyAutoBinder.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/KeyBindings.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/KeyCodes.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/KeySet.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/MiniMap.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/MouseCursor.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/MouseHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/ProfileDrawer.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/QuitBox.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/ResourceBar.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/SelectionKeyHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/ShareBox.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/StartPosSelecter.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/TooltipConsole.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UI/UnitTracker.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/UnsyncedGameCommands.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/WaitCommandsAI.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/WordCompletion.cpp"
	)
SET(sources_engine_Game_Server
		"${CMAKE_CURRENT_SOURCE_DIR}/Server/GameParticipant.cpp"
	)
SET(sources_engine_Game
		${sources_engine_Game_common}
		${sources_engine_Game_Server}
	)

MakeGlobal(sources_engine_Game_common)
MakeGlobal(sources_engine_Game_Server)
MakeGlobal(sources_engine_Game)
