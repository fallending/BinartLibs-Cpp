# Copy files from source directory to destination directory, substituting any
# variables.  Create destination directory if it does not exist.

# With older CMake versions, this macro copies files from one directory to another. If you don't want to substitute variables in the copied files, then change the configure_file @ONLY argument (for example to COPYONLY).

# // https://stackoverflow.com/questions/697560/how-to-copy-directory-from-source-tree-to-binary-tree
macro(configure_files srcDir destDir)
    message(STATUS "Configuring directory ${destDir}")
    make_directory(${destDir})

    file(GLOB templateFiles RELATIVE ${srcDir} ${srcDir}/*)
    foreach(templateFile ${templateFiles})
        set(srcTemplatePath ${srcDir}/${templateFile})
        if(NOT IS_DIRECTORY ${srcTemplatePath})
            message(STATUS "Configuring file ${templateFile}")
            configure_file(
                    ${srcTemplatePath}
                    ${destDir}/${templateFile}
                    @ONLY)
        endif(NOT IS_DIRECTORY ${srcTemplatePath})
    endforeach(templateFile)
endmacro(configure_files)