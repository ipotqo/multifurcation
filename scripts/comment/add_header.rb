#! /usr/bin/env ruby

module DOXYGEN

    START = "/**"
    COMMENT = " * "
    FINISH = " */"

    ALIGNMENT = 6

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
    fo.puts DOXYGEN::FINISH
    File.foreach(uncommented_file) do |line|
        fo.puts line
    end
end

# TODO
# Check if there is already a header before adding (or provide option to replace)
# Rename Files (Overwrite but Keep Original)
# Update .gitignore to not add *_uncommented.cpp and *_uncommented.hpp