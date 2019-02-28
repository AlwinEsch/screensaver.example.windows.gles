# screensaver.example.windows.gles
***Example addon about using Open GL | ES in Kodi on Windows***

This addon shows how [Open Graphics Library for Embedded Systems (OpenGL ES)](https://en.wikipedia.org/wiki/OpenGL_ES) can be used in Kodi on Windows.
It is therefore not to be regarded as a regular addon, as it only displays a fixed triangle and nothing else. Furthermore, this only serves to how this interface can be integrated into an addon. This is achieved by using [Google Angle](https://github.com/google/angle).

To achieve this, only a few changes have to be made in the CMake of your own addon.

To introduce the necessary dependencies into your own addon, the CMake files that are declarable here can be used.
#### This would be necessary in this case:

| File                                          | Description
|-----------------------------------------------|---------------------------------
| ./FindOpenGLES.cmake                          | A CMake search script for all OS which also integrates Angle
| ./depends/windows/angle/0001-fix-uwp.patch    | Patch to use the addon on Windows Store
| ./depends/windows/angle/CMakeLists.txt        | To create the angle-based dependency
| ./depends/windows/angle/angle.sha256          | The check sum of the Angle source code based on sha256
| ./depends/windows/angle/angle.txt             | The URL from where this dependency is loaded

>**Note**: There are no changes in the source code of the addon (if this already supports Open GL ES).

#### To take advantage of this, the following should at least be available at the addon CMakeLists.txt
```cmake
find_package(OpenGLES REQUIRED)
set(DEPLIBS ${OPENGLES_LIBRARIES})
set(INCLUDES ${OPENGLES_INCLUDE_DIR})
add_definitions(${OPENGLES_DEFINITIONS})
```

## Example build instructions
1. `git clone https://github.com/xbmc/xbmc`
2. `git clone https://github.com/xbmc/screensaver.example.windows.gles`
3. `cd screensaver.example.windows.gles && mkdir build && cd build`
4. `cmake -DADDONS_TO_BUILD=screensaver.example.windows.gles -DADDON_SRC_PREFIX=../.. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=C:/Users/%YOUR_USER%/AppData/Roaming/Kodi/addons -DPACKAGE_ZIP=1 %YOUR_KODI_PATH%/xbmc/cmake/addons`
5. `cmake --build . --config Release`
