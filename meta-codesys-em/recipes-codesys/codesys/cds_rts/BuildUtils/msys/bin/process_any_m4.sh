#!/bin/sh
# **********************************************************************************************************
# * Usage:
# * $0 <script name>
# * $* <m4file>[Dep|Itf].m4
# **********************************************************************************************************


function process_dep {

	DEP_M4FILE=$1
	DEP_M4FILE_TMP=${1/%.m4/__.m4}
	DEP_HFILE=${1/%.m4/.h}
	CPPFILE=${1/%Dep.m4/.cpp}

	echo "processing: $DEP_M4FILE -> $DEP_HFILE -> $CPPFILE"


	BUILDUTILSPATH_bin=$(dirname $0)
	BUILDUTILSPATH_M4DEF=$(dirname $0)/../../M4Defs

	COMPONENTS=$(dirname $0)/../../../Components/

	cp $DEP_M4FILE $DEP_M4FILE_TMP
	dos2unix $DEP_M4FILE_TMP >&/dev/null
	m4 -I$BUILDUTILSPATH_bin -I$BUILDUTILSPATH_M4DEF -I$COMPONENTS -I../ Implementation.m4 - < "$DEP_M4FILE_TMP" > "$DEP_HFILE"
	m4 -I$BUILDUTILSPATH_bin -I$BUILDUTILSPATH_M4DEF -I$COMPONENTS -I../ C++Wrapper.m4 - < "$DEP_M4FILE_TMP" > "$CPPFILE"
	dos2unix $DEP_HFILE >&/dev/null
	unix2dos $DEP_HFILE >&/dev/null
	dos2unix $CPPFILE >&/dev/null
	
	rm $DEP_M4FILE_TMP;

}

function process_itf {

	ITF_M4FILE=$1
	ITF_M4FILE_TMP=${1/%.m4/__.m4}
	ITF_HFILE=${1/%.m4/.h}

	echo "processing: $ITF_M4FILE -> $ITF_HFILE"

	BUILDUTILSPATH_bin=$(dirname $0)
	BUILDUTILSPATH_M4DEF=$(dirname $0)/../../M4Defs

	COMPONENTS=$(dirname $0)/../../../Components/

	cp $ITF_M4FILE $ITF_M4FILE_TMP
	dos2unix $ITF_M4FILE_TMP >&/dev/null
	m4 -I$BUILDUTILSPATH_bin -I$BUILDUTILSPATH_M4DEF Exports.m4 - < "$ITF_M4FILE_TMP" > "$ITF_HFILE"
	dos2unix $ITF_HFILE >&/dev/null
	unix2dos $ITF_HFILE >&/dev/null
	
	rm $ITF_M4FILE_TMP;
}


for m4file in "$@"
do     
	#echo $m4file
	if [ ! -f $m4file ];then
		echo "File does not exist: $m4file"
		echo "please provide a valid *.m4 file"
	else
		
		if [[ "$m4file" == *Itf.m4 ]]; then
			process_itf $m4file
		elif [[ "$m4file" == *Dep.m4 ]]; then
			process_dep $m4file
		else
			echo "File is no Itf or Dep m4 file!"			
		fi
		
		
	fi
		
	
done


