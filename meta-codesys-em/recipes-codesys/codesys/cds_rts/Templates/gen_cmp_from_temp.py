#############################################################################
# Author:       Sadra Mostashar - 3s-Smart Software Solutions GmbH
# Module:       gen_cmp_from_temp.py
# License:      Read LICENSE
# Description:  Python script for template-based component generation usable
#               by version 2.7 and above
# ---------------------------------------------------------------------------

import os
import sys
import fileinput
import shutil
import errno
import argparse
import optparse
import io
from contextlib import contextmanager

# get current working directory
directory = os.getcwd()+"/"
version = sys.version

# show usage
def Usage():
    print("\nUse the following input format\n")
    print("Usage: "+sys.argv[0]+" -t <template> -c <component name> -FLAGS")

#############################################################################
# Author:       Martijn Pieters
# Source:       Zopatista.com
# Title:        Easy in-place file rewriting
# Webpage:      http://www.zopatista.com/python/2013/11/26/inplace-file-rewriting/
# License:      Read LICENSE
# Description:  The function inplace and its usage has been employed here from
#               the aforementioned author under Creative Commons 3.0 license.
# ---------------------------------------------------------------------------

@contextmanager
def inplace(filename, mode='r', buffering=-1, encoding=None, errors=None, newline=None, backup_extension=None):
    """Allow for a file to be replaced with new content.

    yields a tuple of (readable, writable) file objects, where writable
    replaces readable.

    If an exception occurs, the old file is restored, removing the
    written data.

    mode should *not* use 'w', 'a' or '+'; only read-only-modes are supported.

    """

    # move existing file to backup, create new file with same permissions
    # borrowed extensively from fileinput module
    if set(mode).intersection('wa+'):
        raise ValueError('Only read-only file modes can be used')

    backupFilename = filename + (backup_extension or os.extsep + 'bak')
    try:
        os.unlink(backupFilename)
    except os.error:
        pass
    os.rename(filename, backupFilename)
    readable = io.open(backupFilename, mode, buffering=buffering, encoding=encoding, errors=errors, newline=newline)

    try:
        perm = os.fstat(readable.fileno()).st_mode
    except OSError:
        writable = open(filename, 'w' + mode.replace('r', ''),
                buffering=buffering, encoding=encoding, errors=errors, newline=newline)

    else:
        os_mode = os.O_CREAT | os.O_WRONLY | os.O_TRUNC
        if hasattr(os, 'O_BINARY'):
            os_mode |= os.O_BINARY
        fd = os.open(filename, os_mode, perm)
        writable = io.open(fd, "w" + mode.replace('r', ''), buffering=buffering, encoding=encoding, errors=errors, newline=newline)

        try:
            if hasattr(os, 'chmod'):
                os.chmod(filename, perm)
        except OSError:
            pass

    try:
        yield readable, writable
    except Exception:
        # move backup back
        try:
            os.unlink(filename)
        except OS.error:
            pass
        os.rename(backupFilename, filename)
        raise
    finally:
        readable.close()
        writable.close()
        try:
            os.unlink(backupFilename)
        except os.error:
            pass

#############################################################################

def inlineReplace(infh, outfh, temp, comp=None, cue=None):
    reader = infh
    writer = outfh

    # if comp given, replace temp string with it
    if comp != None:
        for line in reader:
            # if cue string not given, modify all lines
            if cue == None:
                writer.write(line.replace(temp, comp))
            # if cue string given, modify only lines containing it
            else:
                if cue in line:
                    writer.write(line.replace(temp, comp))
                else:
                    writer.write(line)
    # if comp not given, replace entire line with temp string
    else:
        for line in reader:
            # if cue string not given, modify all lines
            if cue == None:
                writer.write(temp)
            # if cue string given, modify only lines containing it
            else:
                if cue in line:
                    writer.write(temp)
                else:
                    writer.write(line)

    reader.close()
    writer.close()
    infh.close()
    outfh.close()

# filename: file to modify
# temp:     template name string to replace with comp, if comp is given
#           if comp is not given, temp will replace the entire line
# comp:     if given, component name string that overwrites template string
# cue:      string as a clue to specify a certain line in text
def genInlineReplace(filename, temp, comp=None, cue=None):
    if version.startswith("2.7"):
        with inplace(filename, 'rb') as (infh, outfh):
            inlineReplace(infh, outfh, temp, comp=comp, cue=cue)
    elif version.startswith("3"):
        # NOTE: due to encoding constraints, using Python 3 at the moment will ignore rewriting
        # some special characters such as copyright sign.
        # TODO: enable rewriting of special characters such as copyright sign
        with inplace(filename, 'r', newline='', errors='ignore') as (infh, outfh):
            inlineReplace(infh, outfh, temp, comp=comp, cue=cue)

# src: source directory to be copied
# dst: name for destination directory for the new component
# function for copying directory from source template to new component
def CopyCmp(src, dst):
    try:
        shutil.copytree(src, dst)
    except OSError as exc:
        # only copy if a directory
        if exc.errno == errno.ENOTDIR:
            print("src file not a directory")
        else:
            raise

# template: name string of the template for the new component
# cmpName: name string of the component to be generated
# function for generating new component based on template
# it will first copy from the template directory, then rename
# and modify the contents of the files contained. However,
# due to the CRC control, it will not modify CODESYS project
# and library files that will otherwise be curropted.
def CreateComponent(template, cmpName):
    # use current directory as global variable
    global directory
    global version
    # first copy the template to the target name, if it already doens't exist
    if os.path.isdir(directory+cmpName) == False:
        CopyCmp(template, cmpName)
    # for every file in the component directory
    for filename in os.listdir(directory+cmpName):
        # first modify the content of every file in the directory, except subdirectories, project files and library files
        if os.path.isdir(directory+cmpName+"/"+filename) == False and filename.endswith(".project") == False and filename.endswith(".projectarchive") == False and filename.endswith(".library") == False:
            # open each component for renaming every instance of the template name
            # input filename string must contain absolute path string
            filenameStr = directory + cmpName + "/" + filename
            genInlineReplace(filenameStr, template, cmpName)

        # then, rename each file in the current directory named after the template to the component name
        if filename.startswith(template):
            # keep the remaining end part of each file name
            suffix = filename.replace(template, "")
            # construct old file name path string
            oldFileName = os.path.join(directory+cmpName, filename)
            # construct new file name path string
            newFileName = os.path.join(directory+cmpName, cmpName+suffix)
            os.rename(oldFileName, newFileName)

        # in the subdirectories, if the exist
        isSubDir = directory+cmpName+"/"+filename
        if os.path.isdir(isSubDir) == True:
            for subFilename in os.listdir(isSubDir):
                # first rename each instance of the template name in the file contents
                # input filename string must contain absolute path string
                subFilenameStr = isSubDir+"/"+subFilename
                # Quick fix for deleting autogenerated directories under Windows
                # from .sln
                if os.path.isdir(subFilenameStr):
                    shutil.rmtree(subFilenameStr)
                else:
                    genInlineReplace(subFilenameStr, template, cmpName)
                    # then rename each file
                    if subFilename.startswith(template):
                        suffix = subFilename.replace(template, "")
                        oldSubFilename = os.path.join(isSubDir, subFilename)
                        newSubFilename = os.path.join(isSubDir, cmpName+suffix)
                        os.rename(oldSubFilename, newSubFilename)

# set the target architecture in Makefile
def SetBuildOptions(cmpName, targetArch):
    makefile = directory + cmpName + "/Linux/Makefile"
    cxxFlagsEmpty = "CXXFLAGS = -DTRG_"
    cxxFlagsTarget = cxxFlagsEmpty + targetArch
    # replace entire line
    genInlineReplace(makefile, cxxFlagsTarget, cue=cxxFlagsEmpty)

print(sys.version)

# parse the input arguments from the terminal
argparser = argparse.ArgumentParser(description='Process arguments for component/driver generator')
argparser.add_argument("-t", "--template", help="template which is used for generating component/driver")
argparser.add_argument("-c", "--cmpName", help="name for the target component")
argparser.add_argument("-a", "--trgArch", help="target architecture, options (only capital letter): X86 | PPC | ARM | CORTEX")
args = argparser.parse_args()

if args.template != None:
	print("Input template: "+args.template)

if args.cmpName != None:
	print("Output component name "+args.cmpName)

# create component only if the template exists and the target component has not already been made
if args.template != None and args.cmpName != None:
	if os.path.isdir(directory+args.template) == True and os.path.isdir(directory+args.cmpName) == False:
		CreateComponent(args.template, args.cmpName)
		if args.trgArch is not None:
			SetBuildOptions(args.cmpName, args.trgArch)
	else:
		print("Either the given template does not exist, or the target component already exists")
else:
	Usage()
