#!/usr/bin/zsh

# Update Doxygen Documentation
doxygen

# Push to GitHub Pages
index_dir=doc/html
git subtree push --prefix $index_dir origin gh-pages