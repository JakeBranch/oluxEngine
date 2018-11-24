cmake_minimum_required(VERSION 2.6)
project(OLUXENGINE)

include_directories(
	src
	contrib
)	

if(MSVC)
	include_directories(
		contrib/msvc-windows-x86/GLEW/include
		contrib/msvc-windows-x86/SDL2/include
		contrib/msvc-windows-x86/openal-soft/include
    		contrib/msvc-windows-x86/ogg/include
    		contrib/msvc-windows-x86/vorbis/include

	)

	link_directories(
		${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/lib/x86
		${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/GLEW/lib
		${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/openal-soft/lib
   		${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/ogg/lib
    		${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/vorbis/lib
	)
endif()

if(MSVC)
	add_definitions(-DSDL_MAIN_HANDLED)
endif()

add_library(
	oluxEngine
	src/oluxEngine/Core.cpp
	src/oluxEngine/Entity.cpp
	src/oluxEngine/Component.cpp
	src/oluxEngine/VertexArray.cpp
	src/oluxEngine/VertexBuffer.cpp
	src/oluxEngine/ShaderProgram.cpp
	src/oluxEngine/MeshRenderer.cpp
	src/oluxEngine/Resources.cpp
	src/oluxEngine/Resource.cpp
	src/oluxEngine/Texture.cpp
	src/oluxEngine/Sound.cpp
	src/oluxEngine/Exception.cpp
	src/oluxEngine/Exception.cpp
	src/oluxEngine/Camera.cpp
	src/oluxEngine/Keyboard.cpp
	src/oluxEngine/Mouse.cpp
	src/oluxEngine/Transform.cpp
	src/oluxEngine/Light.cpp
	src/oluxEngine/Material.cpp
	src/oluxEngine/DirectionalLight.cpp
	src/oluxEngine/PointLight.cpp
	src/oluxEngine/SpotLight.cpp
	src/oluxEngine/Mesh.cpp
	src/oluxEngine/StaticModelCollider.cpp
	src/oluxEngine/tribox.cpp
	src/oluxEngine/RenderTexture.cpp
	src/oluxEngine/PostProcessor.cpp
	src/oluxEngine/Gui.cpp
	src/oluxEngine/BoxCollider.cpp
)

if(MSVC)
	target_link_libraries(oluxEngine
		SDL2 glew32 opengl32 OpenAL32 ogg vorbis vorbisfile
	)
else()
	target_link_libraries(oluxEngine
		SDL2 GLU GLEW GL AL ogg vorbis vorbisfile
	)
endif()

add_executable(
	game
	src/game/main.cpp
	src/game/TestScene.cpp
	src/game/TestScene.h
	src/game/Environment.cpp
	src/game/Environment.h
	src/game/Player.cpp
	src/game/Player.h
	src/game/MainMenu.cpp
	src/game/MainMenu.h
	src/game/GameScene.cpp
	src/game/GameScene.h
	contrib/stb_image/stb_image.cpp
)

target_link_libraries(game oluxEngine)

if(MSVC)
	add_custom_command(TARGET game POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/lib/x86/SDL2.dll"
		"$<TARGET_FILE_DIR:game>"
	)

	add_custom_command(TARGET game POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/GLEW/bin/glew32.dll"
		"$<TARGET_FILE_DIR:game>"
	)

	add_custom_command(TARGET game POST_BUILD
    		COMMAND ${CMAKE_COMMAND} -E copy_if_different
      		"${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/openal-soft/bin/OpenAL32.dll"
      		"$<TARGET_FILE_DIR:game>"
  	)
endif()