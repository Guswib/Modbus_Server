@echo off
::
::
set BASE_Folder=Virtual_Instrument
set SRCPath=%UserProfile%\Documents\GitHub\%BASE_Folder%
set SRCPath_SRC=%SRCPath%\src
set ArduinoLibPath=%UserProfile%\Documents\Arduino\libraries\%BASE_Folder%
set ArduinoLibPath_SRC=%ArduinoLibPath%\src
::
echo %SRCPath%
::
mkdir %ArduinoLibPath%
mkdir %ArduinoLibPath_SRC%
::
echo %ArduinoLibPath_SRC%
echo %SRCPath%
::
copy "%SRCPath%\lib*.*" "%ArduinoLibPath%"
copy "%SRCPath_SRC%\Virtual*.*" "%ArduinoLibPath_SRC%"
::copy "C:\Users\Gustav\Documents\GitHub\Virtual_Potentiostat\src\Virtual*" "C:\Users\Gustav\Documents\Arduino\libraries\Virtual_Potentiostat\src" /Y
::copy "C:\Users\Gustav\Documents\GitHub\Virtual_Potentiostat\library.*" "C:\Users\Gustav\Documents\Arduino\libraries\Virtual_Potentiostat" /Y
::copy "C:\Users\Gustav\Documents\GitHub\Virtual_Potentiostat\examples\Virtual_Potentiostat\*" "C:\Users\Gustav\Documents\Arduino\libraries\Virtual_Potentiostat\examples\Virtual_Potentiostat" /Y
    
::copy "C:\Users\gustav.wiberg\Documents\GitHub\Virtual_Potentiostat\src\Virtual*" "C:\Users\gustav.wiberg\Documents\Arduino\libraries\Virtual_Potentiostat\src" /Y
::copy "C:\Users\gustav.wiberg\Documents\GitHub\Virtual_Potentiostat\library.*" "C:\Users\gustav.wiberg\Documents\Arduino\libraries\Virtual_Potentiostat" /Y
::copy "C:\Users\gustav.wiberg\Documents\GitHub\Virtual_Potentiostat\examples\Virtual_Potentiostat\*" "C:\Users\gustav.wiberg\Documents\Arduino\libraries\Virtual_Potentiostat\examples\Virtual_Potentiostat" /Y
    