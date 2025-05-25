" 使用系统剪切板
set clipboard=unnamedplus

" 不与Vi兼容
set nocompatible

set showcmd
set encoding=utf-8
" 启用256色
set t_Co=256
" 开启文件类型检查，并且载入与该类型对应的缩进规则，比如.py
filetype indent on

" 按下回车键后，下一行的缩进会自动跟上一行的缩进保持一致
set autoindent
" 按下 Tab 键时，Vim 显示的空格数
set tabstop=2
" 由于 Tab 键在不同的编辑器缩进不一致，该设置自动将 Tab 转为空格
"set expandtab
"" Tab 转为多少个空格
"set softtabstop=2

set nu
set hls
"set textwidth=80
set showmatch
set incsearch
set autochdir
syntax on

" 支持在Visual模式下，通过C-y复制到系统剪切板
vnoremap <C-c> "+y
" 支持在normal模式下，通过C-p粘贴系统剪切板
nnoremap <C-p> "*p
