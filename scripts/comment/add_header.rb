#! /usr/bin/env ruby

# ================ CHANGE BELOW HERE ================

module SOFTWARE
    TITLE = "MULTIFURCATION"
    AUTHOR = "TIM PLEASETH"
    HANDLE = "@IPOTQO"
    LINK = "HTTPS//WWW.GITHUB.COM/IPOQTO/MULTIFURCATION"
    LICENSE = "UNLICENSE"
    ROOT = "multifurcation/"
end

# ================ CHANGE ABOVE HERE ================

module DOXYGEN

    START = "/**"
    COMMENT = " * "
    FINISH = " */"

    FOREWORD =
    "\n"\
    "#{SOFTWARE::TITLE} COPYRIGHT (C) 2023 // #{SOFTWARE::AUTHOR} #{SOFTWARE::HANDLE}\n\n"\
    "RELEASED UNDER THE #{SOFTWARE::LICENSE}\n\n"\
    "THIS FILE IS PART OF THE #{SOFTWARE::TITLE} PROJECT:\n#{SOFTWARE::LINK}\n"\
    "\n"\
    "THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" AND ANY\n"\
    "EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES\n"\
    "OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT\n"\
    "SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,\n"\
    "INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED\n"\
    "TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR\n"\
    "BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN\n"\
    "CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN\n"\
    "ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH\n"\
    "DAMAGE."\
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

# content = File.read(uncommented_file)
# brief = content.match /\\brief (?<value>.+)/
# puts brief["value"]

brief = File.read(uncommented_file).match /\\brief (?<value>.+)/

commented_file = uncommented_file.gsub("uncommented", "commented")

puts "add_header.rb | #{uncommented_file} > #{commented_file}"

unedited = File.read(uncommented_file)
code = unedited.sub( /\/\*\*(.|\n)*\*\//, "" )
# puts code

File.open(commented_file, 'w') do |fo|
    fo.puts DOXYGEN::START
    fo.puts DOXYGEN::LABEL( "file", SOFTWARE::ROOT + commented_file )
    fo.puts DOXYGEN::LABEL( "brief", brief["value"] )
    fo.puts DOXYGEN::STATEMENT
    fo.puts DOXYGEN::FINISH
    fo.puts code

    # uncommented_file.sub ( / a(.+)a / , "")

    # File.foreach(uncommented_file) do |line|
    #    fo.puts line
    # end
end

# File.rename ( file_name, new_name )

# TODO
# Check if there is already a header before adding (or provide option to replace)
# Rename Files (Overwrite but Keep Original)
# Update .gitignore to not add *_uncommented.cpp and *_uncommented.hpp
# If there is a brief ... capture it and then reuse it in the reformat
# If there is no brief then ensure that the first comment is not deleted