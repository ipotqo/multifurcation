#! /usr/bin/env ruby

# ================ CHANGE BELOW ================

module SOFTWARE
    TITLE = "MULTIFURCATION"
    AUTHOR = "TIM PLEASETH"
    HANDLE = "@IPOTQO"
    LINK = "HTTPS//WWW.GITHUB.COM/IPOQTO/MULTIFURCATION"
    LICENSE = "THE UNLICENSE"
end

# ================ CHANGE ABOVE ================

module DOXYGEN

    START = "/**"
    COMMENT = " * "
    FINISH = " */"

    FOREWORD =
    "\n"\
    "#{SOFTWARE::TITLE} COPYRIGHT (C) 2023 #{SOFTWARE::AUTHOR} // #{SOFTWARE::HANDLE}\n\n"\
    "This file is included in the multifurcation code under The Unlicense.\n"\
    ""

    STATEMENT = FOREWORD.split(/\r?\n|\r/).each { |line| line.prepend(COMMENT) }

    ALIGNMENT = 8

    def LABEL ( name, value, s_count = ALIGNMENT )
        DOXYGEN::COMMENT + "\\#{name}" + (" " * (s_count - name.length)) + value
    end
    module_function :LABEL
    
end

def locate_file (file)
    File.open (file)
rescue Errno::ENOENT => e
    puts "Error: file #{file} not found."
    puts e.message
    puts e.backtrace
end

uncommented_file = ARGV[0]
locate_file (uncommented_file)

commented_file = uncommented_file.gsub("uncommented", "commented")

puts "add_header.rb | #{uncommented_file} > #{commented_file}"

File.open(commented_file, 'w') do |fo|
    fo.puts DOXYGEN::START
    fo.puts DOXYGEN::LABEL( "file", commented_file )
    fo.puts DOXYGEN::LABEL( "brief", "..." )
    fo.puts DOXYGEN::STATEMENT
    fo.puts DOXYGEN::FINISH
    File.foreach(uncommented_file) do |line|
        fo.puts line
    end
end

# TODO
# Check if there is already a header before adding (or provide option to replace)
# Rename Files (Overwrite but Keep Original)
# Update .gitignore to not add *_uncommented.cpp and *_uncommented.hpp
# If there is a brief ... capture it and then reuse it in the reformat