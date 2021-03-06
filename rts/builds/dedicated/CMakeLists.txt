ADD_DEFINITIONS    (-DDEDICATED ${PIC_FLAG} -DNOT_USING_CREG)
ADD_DEFINITIONS    (-DHEADLESS -DNO_SOUND)
REMOVE_DEFINITIONS (-DSTREFLOP_SSE -DAVI_CAPTURING)
REMOVE_DEFINITIONS (-DTRACE_SYNC -DSYNCDEBUG)

# deactivate signaling-NANs for this library
RemoveFlag("-fsignaling-nans")

# Place executables and shared libs under "build-dir/",
# instead of under "build-dir/rts/"
# This way, we have the build-dir structure more like the install-dir one,
# which makes testing spring in the builddir easier, eg. like this:
# cd build-dir
# SPRING_DATADIR=$(pwd) ./spring
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

SET(ENGINE_SRC_ROOT_DIR "${CMAKE_SOURCE_DIR}/rts")


### Assemble libraries
LIST(APPEND engineDedicatedLibraries ${Boost_REGEX_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_SYSTEM_LIBRARY})
LIST(APPEND engineDedicatedLibraries lua archives 7zip ${SPRING_MINIZIP_LIBRARY} ${ZLIB_LIBRARY})
LIST(APPEND engineDedicatedLibraries headlessStubs)
IF    (UNIX)
	# Needed for dynamically loading shared libraries (on some OS)
	LIST(APPEND engineDedicatedLibraries dl)
ENDIF (UNIX)

IF    (MINGW OR APPLE)
	# Windows:
	# We still need these header files,
	# even if we are not going to link with SDL.
	# We have them available anyway (mingwlibs).
	# OS X:
	# Cocoa requires the SDL libary, whenever the SDL headers are used,
	# due to some #define magic, which is practically impossible to workaround.
	FIND_PACKAGE(SDL REQUIRED)
	INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})
ELSE  (MINGW OR APPLE)
	# Use a direct copy of the GL and SDL headers,
	# as these may not be available on headless systems.
	INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/SDL)
ENDIF (MINGW OR APPLE)


### Assemble the incude dirs
INCLUDE_DIRECTORIES(${ENGINE_SRC_ROOT_DIR}/)
INCLUDE_DIRECTORIES(${ENGINE_SRC_ROOT_DIR}/lib/lua/include/)
INCLUDE_DIRECTORIES(${ENGINE_SRC_ROOT_DIR}/lib/7zip)



### Assemble sources
IF	(UNIX)
	SET(sources_engine_Platform_CrashHandler
		${ENGINE_SRC_ROOT_DIR}/System/Platform/Threading.cpp
		${ENGINE_SRC_ROOT_DIR}/System/Platform/Linux/thread_backtrace.cpp
		${ENGINE_SRC_ROOT_DIR}/System/Platform/Linux/CrashHandler.cpp)
ELSEIF	(WIN32)
	SET(sources_engine_Platform_CrashHandler
		${ENGINE_SRC_ROOT_DIR}/System/Platform/Win/seh.cpp
		${ENGINE_SRC_ROOT_DIR}/System/Platform/Win/CrashHandler.cpp)
ELSE	()
	SET(sources_engine_Platform_CrashHandler
		${ENGINE_SRC_ROOT_DIR}/System/Platform/Threading.cpp
		${ENGINE_SRC_ROOT_DIR}/System/Platform/Mac/CrashHandler.cpp)
ENDIF	()

SET(system_files
	${sources_engine_System_FileSystem}
	${sources_engine_System_Log}
	${sources_engine_System_Net}
	${sources_engine_Platform_CrashHandler}
	${ENGINE_SRC_ROOT_DIR}/System/Config/ConfigHandler.cpp
	${ENGINE_SRC_ROOT_DIR}/System/Config/ConfigLocater.cpp
	${ENGINE_SRC_ROOT_DIR}/System/Config/ConfigSource.cpp
	${ENGINE_SRC_ROOT_DIR}/System/Config/ConfigVariable.cpp
	${ENGINE_SRC_ROOT_DIR}/System/CRC.cpp
	${ENGINE_SRC_ROOT_DIR}/System/Platform/EngineTypeHandler.cpp
	${ENGINE_SRC_ROOT_DIR}/System/Platform/errorhandler.cpp
	${ENGINE_SRC_ROOT_DIR}/System/Platform/Misc.cpp
	${ENGINE_SRC_ROOT_DIR}/System/Platform/CmdLineParams.cpp
	${ENGINE_SRC_ROOT_DIR}/System/Platform/ScopedFileLock.cpp
	${ENGINE_SRC_ROOT_DIR}/System/Platform/Threading.cpp
	${ENGINE_SRC_ROOT_DIR}/System/TdfParser.cpp
	${ENGINE_SRC_ROOT_DIR}/System/GlobalConfig.cpp
	${ENGINE_SRC_ROOT_DIR}/System/Info.cpp
	${ENGINE_SRC_ROOT_DIR}/System/LogOutput.cpp
	${ENGINE_SRC_ROOT_DIR}/System/TimeUtil.cpp
	${ENGINE_SRC_ROOT_DIR}/System/BaseNetProtocol.cpp
	${ENGINE_SRC_ROOT_DIR}/System/LoadSave/Demo.cpp
	${ENGINE_SRC_ROOT_DIR}/System/LoadSave/DemoReader.cpp
	${ENGINE_SRC_ROOT_DIR}/System/LoadSave/DemoRecorder.cpp
	${ENGINE_SRC_ROOT_DIR}/System/AutohostInterface.cpp
	${ENGINE_SRC_ROOT_DIR}/System/SafeCStrings.c
	${ENGINE_SRC_ROOT_DIR}/System/UnsyncedRNG.cpp
	${ENGINE_SRC_ROOT_DIR}/System/Util.cpp
	${ENGINE_SRC_ROOT_DIR}/System/float4.cpp
	${ENGINE_SRC_ROOT_DIR}/System/Log/Backend.cpp
	${ENGINE_SRC_ROOT_DIR}/System/Log/DefaultFilter.cpp
	${ENGINE_SRC_ROOT_DIR}/System/Log/DefaultFormatter.cpp
	${ENGINE_SRC_ROOT_DIR}/System/Log/FramePrefixer.cpp
	${ENGINE_SRC_ROOT_DIR}/System/Log/LogSinkHandler.cpp
	${ENGINE_SRC_ROOT_DIR}/System/Log/LogUtil.c
	${ENGINE_SRC_ROOT_DIR}/System/Log/ConsoleSink.cpp
	${ENGINE_SRC_ROOT_DIR}/System/Misc/SpringTime.cpp
	)
IF    (WIN32)
	LIST(APPEND system_files ${ENGINE_SRC_ROOT_DIR}/System/Platform/Win/WinVersion.cpp)
ENDIF (WIN32)

SET(engineDedicatedSources
	${system_files}
	${sources_engine_Game_Server}
	${sources_engine_System_Log}
	${ENGINE_SRC_ROOT_DIR}/Game/GameServer.cpp
	${ENGINE_SRC_ROOT_DIR}/Game/ClientSetup.cpp
	${ENGINE_SRC_ROOT_DIR}/Game/GameSetup.cpp
	${ENGINE_SRC_ROOT_DIR}/Game/GameData.cpp
	${ENGINE_SRC_ROOT_DIR}/Game/PlayerBase.cpp
	${ENGINE_SRC_ROOT_DIR}/Game/PlayerStatistics.cpp
	${ENGINE_SRC_ROOT_DIR}/Game/GameVersion.cpp
	${ENGINE_SRC_ROOT_DIR}/Game/IVideoCapturing.cpp
	${ENGINE_SRC_ROOT_DIR}/Game/DummyVideoCapturing.cpp
	${ENGINE_SRC_ROOT_DIR}/Game/CommandMessage.cpp
	${ENGINE_SRC_ROOT_DIR}/Game/ChatMessage.cpp
	${ENGINE_SRC_ROOT_DIR}/Game/Action.cpp
	${ENGINE_SRC_ROOT_DIR}/Sim/Misc/TeamBase.cpp
	${ENGINE_SRC_ROOT_DIR}/Sim/Misc/TeamStatistics.cpp
	${ENGINE_SRC_ROOT_DIR}/Sim/Misc/AllyTeam.cpp
	${ENGINE_SRC_ROOT_DIR}/Lua/LuaIO.cpp
	${ENGINE_SRC_ROOT_DIR}/Lua/LuaParser.cpp
	${ENGINE_SRC_ROOT_DIR}/Lua/LuaUtils.cpp
	${ENGINE_SRC_ROOT_DIR}/Map/MapParser.cpp
	)


# Compile dedicated server shared library
ADD_LIBRARY(springserver-static STATIC EXCLUDE_FROM_ALL ${engineDedicatedSources})
Add_Dependencies(springserver-static generateVersionFiles)
TARGET_LINK_LIBRARIES(springserver-static ${engineDedicatedLibraries})
IF    (MINGW)
	TARGET_LINK_LIBRARIES (springserver-static ${WS2_32_LIBRARY} ${IMAGEHLP_LIBRARY})
ENDIF (MINGW)

ADD_LIBRARY(springserver SHARED
		${ENGINE_SRC_ROOT_DIR}/Map/MapParser.cpp
		${sources_engine_System_Log_sinkFile}
		${sources_engine_System_Log_sinkOutputDebugString}
	)
TARGET_LINK_LIBRARIES(springserver springserver-static)

# Compile dedicated server executable
ADD_EXECUTABLE(engine-dedicated
		${ENGINE_SRC_ROOT_DIR}/Map/MapParser.cpp
		${sources_engine_System_Log_sinkConsole}
		${sources_engine_System_Log_sinkFile}
		${sources_engine_System_Log_sinkOutputDebugString}
		main
	)
TARGET_LINK_LIBRARIES(engine-dedicated springserver-static)

### Install the executable
INSTALL(TARGETS springserver     DESTINATION ${LIBDIR})
INSTALL(TARGETS engine-dedicated DESTINATION ${BINDIR})
SET_TARGET_PROPERTIES(engine-dedicated PROPERTIES OUTPUT_NAME "spring-dedicated")


# Only build & install spring-dedicated executable & dependencies
# use cases:
# * make spring-dedicated
# * make install-spring-dedicated
set(springDsDeps
		engine-dedicated
		springserver
		gamedata
		unitsync
	)
add_custom_target(spring-dedicated
	WORKING_DIRECTORY
		"${CMAKE_BINARY_DIR}"
	COMMENT
		"  spring-dedicated: Building all dependencies ..." VERBATIM
	)
add_dependencies(spring-dedicated ${springDsDeps}) # This also works for custom targets

set(springDsInstallDirs
		"rts/builds/dedicated"
		"tools/unitsync"
		"cont"
	)
CreateInstallTarget(spring-dedicated springDsDeps springDsInstallDirs)
