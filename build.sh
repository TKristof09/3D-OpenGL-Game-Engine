BUILD_TARGET="Debug"
ONLY_CMAKE=0
if [ "$#" == 0 ]; then
		BUILD_TARGET="Debug"
else
		BUILD_TARGET="$1"
fi
if [ "$2" != "" ]; then
		ONLY_CMAKE=1
else
		ONLY_CMAKE=0
fi
echo $ONLY_CMAKE
mkdir Build
cd Build
cmake -DCMAKE_BUILD_TYPE="$BUILD_TARGET" -DCMAKE_CXX_COMPILER=g++-8 ../
if [ $ONLY_CMAKE -eq 0 ]; then
	make -j4 VERBOSE=1 
fi
mv compile_commands.json ..
