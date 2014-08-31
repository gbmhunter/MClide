#!/bin/bash


file="package.json"
numDeps=$(cat package.json | jq 'length')
echo "Num deps = $numDeps"
index=0
depLibPaths=""
depLibs=""
depIncludePaths=""
while [ $index -lt $numDeps ];
do
	echo "In while loop"
	myName=$(cat $file | jq "$(echo .[$index].name)")
	echo "Name=$myName"
	myName="${myName%\"}"
	myName="${myName#\"}"
	echo "Stripped Name=$myName"
	relPath=`echo ../$myName`
	echo "relPath=$relPath"
	myRepo=$(cat $file | jq "$(echo .[$index].repo)")
	echo Repo=$myRepo
	myRepo="${myRepo%\"}"
	myRepo="${myRepo#\"}"
	echo "Stripped Repo=$myRepo"
	if [[ -d $relPath ]]; then
		echo "Repo found"
		else
		echo "Repo not found"
		echo $relPath
		git clone $myRepo $relPath
	fi
	# Get build command length
	#buildCmdsLength=$(cat $file | jq '.["$(echo $index)"].buildCmds[0] | length')
	jqCmd=".[$index].buildCmds | length"
	echo "jqCmd = $jqCmd"
	#buildCmdsLength=$(cat $file | \"jq $jqCmd\")
	buildCmdsLength=$(cat $file | jq "$jqCmd")
	echo "Build cmds length = $buildCmdsLength"
	
	
	# Goto directory
	cd $relPath
	
	# Build dependency
	echo "Building dependency..."
	buildCmdIndex=0
	while [ $buildCmdIndex -lt $buildCmdsLength ];
	do
		# Call each build command
		jqCmd=".[$index].buildCmds[$buildCmdIndex].buildCmd"
		echo "jqCmd = $jqCmd"
		buildCmd=$(cat ../ClideCpp/$file | jq "$jqCmd")
		buildCmd="${buildCmd%\"}"
		buildCmd="${buildCmd#\"}"
		echo "Build cmd = $buildCmd"
		$buildCmd
		buildCmdIndex=$(expr $buildCmdIndex + 1)
		#make -C $relPath all
	done
	echo "Finished building dependency."
	cd ../ClideCpp
	# Add to compiler library path, 
	# only if headerOnly is set to no
	jqCmd=".[$index].headerOnly"
	echo "jqCmd = $jqCmd"
	headerOnly=$(cat $file | jq "$jqCmd")
	echo "headerOnly = $headerOnly"
	if [[ $headerOnly == "\"no\"" ]];	then
		echo "Adding to dep lib paths"
		depLibPaths="$depLibPaths -L $relPath"
		depLibs="$depLibs -l $myName"
	fi
	# Increment index
	index=$(expr $index + 1)
done

depIncludePaths="-I../"

echo "depLibPaths = $depLibPaths"
echo "depLibs = $depLibs"
echo "depIncludePaths = $depIncludePaths"

# Finished building dependencies, now lets call make for target module
make all DEP_LIB_PATHS="$depLibPaths" DEP_LIBS="$depLibs" DEP_INCLUDE_PATHS="$depIncludePaths"

	
	