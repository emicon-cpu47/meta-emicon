
BASEPATH=/svn/trunk/
BUILDUTILS_PATH=/svn/trunk/BuildUtils
COMPONENT_ITF_NAME=CmpQtControlItf
COMPONENT_DEP_NAME=CmpQtControlDep
COMPONENT_PATH=$BASEPATH/Components

echo '---- Generating dependency file: '$COMPONENT_DEP_NAME'.h ----'
sh $BUILDUTILS_PATH/msys/bin/generate_dep_withCpp_linux.sh $COMPONENT_DEP_NAME $BUILDUTILS_PATH/msys/bin $BUILDUTILS_PATH/M4Defs $COMPONENT_PATH
#echo '---- Generating interface file: '$COMPONENT_ITF_NAME'.h ----'
#sh $BUILDUTILS_PATH/msys/bin/generate_itf_linux.sh $COMPONENT_ITF_NAME  $BUILDUTILS_PATH/msys/bin $BUILDUTILS_PATH/M4Defs
#echo '---- done generating files ----'

