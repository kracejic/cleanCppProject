# This is an attempt on universal .ycm_extra_conf.py
# You can have one in your home and point to it from your .vimrc with: 
#    let g:ycm_global_ycm_extra_conf = '~/path/.ycm_extra_conf.py'  

# Sources (from oldest to newest):
# https://github.com/Valloric/ycmd/blob/master/cpp/ycm/.ycm_extra_conf.py
# https://jonasdevlieghere.com/a-better-youcompleteme-config/
# https://github.com/arximboldi/dotfiles/blob/master/emacs/.ycm_extra_conf.py
# https://github.com/kracejic/dotfiles

import os
import os.path
import logging
import ycm_core

# Default settings in case no *compile_commands.json* or *.clang_complete* file
# is not found, these and nearest *include* folder are used
BASE_FLAGS = [
    '-Wall',
    '-Wextra',
    '-Wshadow',
    '-Wnon-virtual-dtor',
    '-Wunused',
    '-Wextra',
    '-Wmisleading-indentation',
    '-pedantic',
    '-std=c++14',
    '-xc++',
    '-I/usr/lib/'
    '-I/usr/include/'
]

SOURCE_EXTENSIONS = [
    '.cpp',
    '.cxx',
    '.cc',
    '.c',
    '.m',
    '.mm'
]

HEADER_EXTENSIONS = [
    '.h',
    '.hxx',
    '.hpp',
    '.hh'
]

def is_header_file(filename):
    extension = os.path.splitext(filename)[1]
    return extension in HEADER_EXTENSIONS

def get_some_file_from_database(dbpath):
    import json
    return json.load(open(dbpath))[0]["file"]

def get_compilation_info_for_file(dbpath, database, filename):
    if is_header_file(filename):
        basename = os.path.splitext(filename)[0]
        for extension in SOURCE_EXTENSIONS:
            replacement_file = basename + extension
            if os.path.exists(replacement_file):
                compilation_info = database.GetCompilationInfoForFile(replacement_file)
                if compilation_info.compiler_flags_:
                    return compilation_info
        return database.GetCompilationInfoForFile(
            get_some_file_from_database(dbpath))
    return database.GetCompilationInfoForFile(filename)

def find_nearest(path, target):
    candidate = os.path.join(path, target)
    build_candidate = os.path.join(path, 'build', target)
    if os.path.isfile(candidate) or os.path.isdir(candidate):
        logging.info("Found nearest " + target + " at " + candidate)
        return candidate
    elif os.path.isfile(build_candidate) or os.path.isdir(build_candidate):
        logging.info("Found nearest " + target + " at " + build_candidate)
        return build_candidate
    else:
        parent = os.path.dirname(os.path.abspath(path))
        if(parent == path):
            raise RuntimeError("Could not find " + target)
        return find_nearest(parent, target)

def make_relative_paths_in_flags_absolute(flags, working_directory):
    if not working_directory:
        return list(flags)
    new_flags = []
    make_next_absolute = False
    path_flags = [ '-isystem', '-I', '-iquote', '--sysroot=' ]
    for flag in flags:
        new_flag = flag

        if make_next_absolute:
            make_next_absolute = False
            if not flag.startswith('/'):
                new_flag = os.path.join(working_directory, flag)

        for path_flag in path_flags:
            if flag == path_flag:
                make_next_absolute = True
                break

            if flag.startswith(path_flag):
                path = flag[ len(path_flag): ]
                new_flag = path_flag + os.path.join(working_directory, path)
                break

        if new_flag:
            new_flags.append(new_flag)
    return new_flags


def flags_for_clang_complete(root):
    try:
        clang_complete_path = find_nearest(root, '.clang_complete')
        clang_complete_flags = open(clang_complete_path, 'r').read().splitlines()
        return clang_complete_flags
    except:
        return None

def flags_for_include(root):
    try:
        include_path = find_nearest(root, 'include')
        flags = []
        for dirroot, dirnames, filenames in os.walk(include_path):
            for dir_path in dirnames:
                real_path = os.path.join(dirroot, dir_path)
                flags = flags + ["-I" + real_path]
        return flags
    except:
        return None

def flags_for_compilation_database(root, filename):
    try:
        compilation_db_path = find_nearest(root, 'compile_commands.json')
        compilation_db_dir = os.path.dirname(compilation_db_path)
        logging.info("Set compilation database directory to " + compilation_db_dir)
        compilation_db = ycm_core.CompilationDatabase(compilation_db_dir)
        if not compilation_db:
            logging.info("Compilation database file found but unable to load")
            return None
        compilation_info = get_compilation_info_for_file(
            compilation_db_path, compilation_db, filename)
        if not compilation_info:
            logging.info("No compilation info for " + filename + " in compilation database")
            return None
        return make_relative_paths_in_flags_absolute(
            compilation_info.compiler_flags_,
            compilation_info.compiler_working_dir_)
    except:
        return None

def flags_for_file(filename):
    root = os.path.realpath(filename)
    compilation_db_flags = flags_for_compilation_database(root, filename)
    if compilation_db_flags:
        final_flags = compilation_db_flags
    else:
        final_flags = BASE_FLAGS
        clang_flags = flags_for_clang_complete(root)
        if clang_flags:
            final_flags = final_flags + clang_flags
        include_flags = flags_for_include(root)
        if include_flags:
            final_flags = final_flags + include_flags
    return {
        'flags': final_flags,
        'do_cache': True
    }

FlagsForFile = flags_for_file
