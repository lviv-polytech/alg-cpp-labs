# Use DEV terminal
MSBUILD = MSBuild

clean:
	MSBuild FirstSetupCpp.Tests/FirstSetupCpp.Tests.vcxproj /t:Clean,Rebuild /p:Configuration=Debug /p:Platform=x64

compile-tests: clean
	$(MSBUILD) FirstSetupCpp.Tests/FirstSetupCpp.Tests.vcxproj /t:Build /p:Configuration=Debug /p:Platform=x64

run-tests: compile-tests
	.\FirstSetupCpp.Tests\x64\Debug\FirstSetupCpp.Tests.exe
