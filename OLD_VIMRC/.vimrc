"""""""""""""""""""""""""""""""""""""""""""""""
"""""""""""""""""""""""""""""""""""""""""""""""
"              _
"       __   _(_)_ __ ___  _ __ ___
"       \ \ / / | '_ ` _ \| '__/ __|
"        \ V /| | | | | | | | | (__
"       (_)_/ |_|_| |_| |_|_|  \___|
"
"""""""""""""""""""""""""""""""""""""""""""""""
"""""""""""""""""""""""""""""""""""""""""""""""

"set pythonthreedll=python38.dll " my python version
set exrc                        " to read local .vimrc files
set secure                      " fixes some dangers of exrc


"-------------VUNDLE--------------

set noeb vb t_vb=
set nocompatible                " be iMproved, required
filetype off                    " required
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'

Plugin 'preservim/nerdtree'
Plugin 'junegunn/fzf', { 'do': { -> fzf#install() } }
Plugin 'junegunn/fzf.vim'
Plugin 'vim-airline/vim-airline'
Plugin 'vim-airline/vim-airline-themes'

Plugin 'neoclide/coc.nvim', {'branch': 'release'}
Plugin 'puremourning/vimspector'

Plugin 'prabirshrestha/vim-lsp'
Plugin 'jackguo380/vim-lsp-cxx-highlight'
"Plugin 'mattn/vim-lsp-settings'

Plugin 'lervag/vimtex'

Plugin 'morhetz/gruvbox'
Plugin 'jaredgorski/SpaceCamp'
Plugin 'tomasiser/vim-code-dark'


"Plugin 'rdnetto/YCM-Generator', { 'branch': 'stable'}
"Plugin 'xolox/vim-misc',
"Plugin 'xolox/vim-easytags'

"Plugin 'grwlf/xkb-switch'
"Plugin 'SirVer/ultisnips'
call vundle#end()            " required
"set runtimepath+=~/.vim/bundle/YouCompleteMe/
"set runtimepath+=~/.vim/bundle/YouCompleteMe/plugin/youcompleteme.vim
set runtimepath+=/usr/include/x86_64-linux-gnu/c++/9
set runtimepath+=/usr/local/include
filetype plugin indent on    " required

"-------------PLUGIN SETTINGS--------------

"make first column 
set signcolumn=yes              

"""YouCompleteMe
"let g:ycm_max_diagnostics_to_display = 0
"let g:ycm_seed_identifiers_with_syntax=1
"let g:ycm_always_populate_location_list=1
"let g:ycm_global_ycm_extra_conf = '/home/alexandr/.vim/bundle/youcompleteme/third_party/ycmd/.ycm_extra_conf.py'
"let g:ycm_confirm_extra_conf=0
"let g:ycm_collect_identifiers_from_tag_files = 1

" Let clangd fully control code completion
"let g:ycm_clangd_uses_ycmd_caching = 0
" Use installed clangd, not YCM-bundled clangd which doesn't get updates.
"let g:ycm_clangd_binary_path = exepath("clangd")

"""AIRLINE

"""LSP
let g:lsp_cxx_hl_use_text_props=1

"""CoC

let g:coc_global_extensions = ['coc-json', 'coc-clangd']

" TextEdit might fail if hidden is not set.
set hidden

" Some servers have issues with backup files, see #649.
set nobackup
set nowritebackup

" Give more space for displaying messages.
set cmdheight=2

" Having longer updatetime (default is 4000 ms = 4 s) leads to noticeable
" delays and poor user experience.
set updatetime=300

" Don't pass messages to |ins-completion-menu|.
set shortmess+=c

" Use tab for trigger completion with characters ahead and navigate.
" NOTE: Use command ':verbose imap <tab>' to make sure tab is not mapped by
" other plugin before putting this into your config.
inoremap <silent><expr> <TAB>
      \ pumvisible() ? "\<C-n>" :
      \ <SID>check_back_space() ? "\<TAB>" :
      \ coc#refresh()
inoremap <expr><S-TAB> pumvisible() ? "\<C-p>" : "\<C-h>"

function! s:check_back_space() abort
  let col = col('.') - 1
  return !col || getline('.')[col - 1]  =~# '\s'
endfunction

" Use <c-space> to trigger completion.
if has('nvim')
  inoremap <silent><expr> <c-space> coc#refresh()
else
  inoremap <silent><expr> <c-@> coc#refresh()
endif

" Use `[g` and `]g` to navigate diagnostics
" Use `:CocDiagnostics` to get all diagnostics of current buffer in location list.
nmap <silent> [g <Plug>(coc-diagnostic-prev)
nmap <silent> ]g <Plug>(coc-diagnostic-next)

nmap <silent> gd <Plug>(coc-definition)
nmap <silent> gy <Plug>(coc-type-definition)
nmap <silent> gi <Plug>(coc-implementation)
nmap <silent> gr <Plug>(coc-references)

" Use K to show documentation in preview window.
nnoremap <silent> K :call <SID>show_documentation()<CR>

function! s:show_documentation()
  if (index(['vim','help'], &filetype) >= 0)
    execute 'h '.expand('<cword>')
  elseif (coc#rpc#ready())
    call CocActionAsync('doHover')
  else
    execute '!' . &keywordprg . " " . expand('<cword>')
  endif
endfunction

" Highlight the symbol and its references when holding the cursor.
autocmd CursorHold * silent call CocActionAsync('highlight')

" Symbol renaming.
nmap <leader>rn <Plug>(coc-rename)

" Formatting selected code.
xmap <leader>f  <Plug>(coc-format-selected)
nmap <leader>f  <Plug>(coc-format-selected)

augroup mygroup
  autocmd!
  " Setup formatexpr specified filetype(s).
  autocmd FileType typescript,json setl formatexpr=CocAction('formatSelected')
  " Update signature help on jump placeholder.
  autocmd User CocJumpPlaceholder call CocActionAsync('showSignatureHelp')
augroup end

" Applying codeAction to the selected region.
" Example: `<leader>aap` for current paragraph
xmap <leader>a  <Plug>(coc-codeaction-selected)
nmap <leader>a  <Plug>(coc-codeaction-selected)

" Remap keys for applying codeAction to the current buffer.
nmap <leader>ac  <Plug>(coc-codeaction)
" Apply AutoFix to problem on the current line.
nmap <leader>qf  <Plug>(coc-fix-current)

" Map function and class text objects
" NOTE: Requires 'textDocument.documentSymbol' support from the language server.
xmap if <Plug>(coc-funcobj-i)
omap if <Plug>(coc-funcobj-i)
xmap af <Plug>(coc-funcobj-a)
omap af <Plug>(coc-funcobj-a)
xmap ic <Plug>(coc-classobj-i)
omap ic <Plug>(coc-classobj-i)
xmap ac <Plug>(coc-classobj-a)
omap ac <Plug>(coc-classobj-a)

" Remap <C-f> and <C-b> for scroll float windows/popups.
if has('nvim-0.4.0') || has('patch-8.2.0750')
  nnoremap <silent><nowait><expr> <C-f> coc#float#has_scroll() ? coc#float#scroll(1) : "\<C-f>"
  nnoremap <silent><nowait><expr> <C-b> coc#float#has_scroll() ? coc#float#scroll(0) : "\<C-b>"
  inoremap <silent><nowait><expr> <C-f> coc#float#has_scroll() ? "\<c-r>=coc#float#scroll(1)\<cr>" : "\<Right>"
  inoremap <silent><nowait><expr> <C-b> coc#float#has_scroll() ? "\<c-r>=coc#float#scroll(0)\<cr>" : "\<Left>"
  vnoremap <silent><nowait><expr> <C-f> coc#float#has_scroll() ? coc#float#scroll(1) : "\<C-f>"
  vnoremap <silent><nowait><expr> <C-b> coc#float#has_scroll() ? coc#float#scroll(0) : "\<C-b>"
endif

" Use CTRL-S for selections ranges.
" Requires 'textDocument/selectionRange' support of language server.
nmap <silent> <C-s> <Plug>(coc-range-select)
xmap <silent> <C-s> <Plug>(coc-range-select)

" Add `:Format` command to format current buffer.
command! -nargs=0 Format :call CocAction('format')

" Add `:Fold` command to fold current buffer.
command! -nargs=? Fold :call     CocAction('fold', <f-args>)

" Add `:OR` command for organize imports of the current buffer.
command! -nargs=0 OR   :call     CocAction('runCommand', 'editor.action.organizeImport')

" Add (Neo)Vim's native statusline support.
" NOTE: Please see `:h coc-status` for integrations with external plugins that
" provide custom statusline: lightline.vim, vim-airline.
set statusline^=%{coc#status()}%{get(b:,'coc_current_function','')}

" Mappings for CoCList
" Show all diagnostics.
nnoremap <silent><nowait> <space>a  :<C-u>CocList diagnostics<cr>
" Manage extensions.
nnoremap <silent><nowait> <space>e  :<C-u>CocList extensions<cr>
" Show commands.
nnoremap <silent><nowait> <space>c  :<C-u>CocList commands<cr>
" Find symbol of current document.
nnoremap <silent><nowait> <space>o  :<C-u>CocList outline<cr>
" Search workspace symbols.
nnoremap <silent><nowait> <space>s  :<C-u>CocList -I symbols<cr>
" Do default action for next item.
nnoremap <silent><nowait> <space>j  :<C-u>CocNext<CR>
" Do default action for previous item.
nnoremap <silent><nowait> <space>k  :<C-u>CocPrev<CR>
" Resume latest coc list.
nnoremap <silent><nowait> <space>p  :<C-u>CocListResume<CR>

" vimspector
let g:vimspector_enable_mappings = 'HUMAN'

"F5	            <Plug>VimspectorContinue	                    When debugging, continue. Otherwise start debugging.
"F3	            <Plug>VimspectorStop	                        Stop debugging.
"F4	            <Plug>VimspectorRestart	                        Restart debugging with the same configuration.
"F6	            <Plug>VimspectorPause	                        Pause debuggee.
"F9	            <Plug>VimspectorToggleBreakpoint	            Toggle line breakpoint on the current line.
"<leader>F9	    <Plug>VimspectorToggleConditionalBreakpoint	    Toggle conditional line breakpoint on the current line.
"F8	            <Plug>VimspectorAddFunctionBreakpoint	        Add a function breakpoint for the expression under cursor
"<leader>F8	    <Plug>VimspectorRunToCursor	                    Run to Cursor
"F10	        <Plug>VimspectorStepOver	                    Step Over
"F11	        <Plug>VimspectorStepInto	                    Step Into
"F12	        <Plug>VimspectorStepOut	                        Step out of current function scope


"nnoremap <leader>dd :call vimspector#Launch()<CR>
"nnoremap <leader>de :call vimspector#Reset()<CR>
"nnoremap <leader>dj :call vimspector#StepInto()<CR>
"nnoremap <leader>dn :call vimspector#StepOver()<CR>
"nnoremap <leader>dk :call vimspector#StepOut()<CR>
"nnoremap <leader>dr :call vimspector#Restart()<CR>
"nnoremap <leader>d<space> :call vimspector#Continue()<CR>
"nnoremap <leader>db :call vimspector#ToggleBreakpoint()<CR>
"nnoremap <leader>dcb :call vimspector#ToggleConditionalBreakpoint()<CR>
"
"nnoremap <leader>dgc :call GotoWindow(g:vimspector_session_windows.code)<CR>
"nnoremap <leader>dgv :call GotoWindow(g:vimspector_session_windows.variables)<CR>
"nnoremap <leader>dgs :call GotoWindow(g:vimspector_session_windows.stack_trace)<CR>
"nnoremap <leader>dgo :call GotoWindow(g:vimspector_session_windows.output)<CR>

"let g:easytags_async=1
"let g:easytags_auto_highlight=0
"let g:easytags_syntax_keyword = 'always'

set completeopt=longest,menu



"let g:netrw_liststyle = 3

"-------------GENERAL SETTINGS--------------

"""make good ctags
"set tags+=$HOME/ar13/tags;
"set tags+=/opencv/3.4.9/tags;
"set tags+=/usr/include/c++/9;

syntax on
set background=dark
colorscheme gruvbox
"colorscheme codedark

set shellcmdflag=-ic "make vim use current bash settings

set history=10000

"fix background to be transparent
"hi Normal guibg=NONE ctermbg=NONE

"""wildmenu lazyredraw visualbell number ruler expandtab tabstop shiftwidth autoindent smarttab smartindent
set wmnu lz vb nu ru et ts=4 sw=4 ai sta si 
set gfn=consolas "guifont
set encoding=utf-8
set t_Co=256

"""Disable autocommenting
autocmd FileType * setlocal formatoptions-=c formatoptions-=r formatoptions-=o

set spr sb "splitright splitbelow
set hls is ar "hlsearch incsearch autoread

set mouse=a 
set showcmd

set whichwrap+=<,>,[,]
set backspace=indent,eol,start

command! -nargs=0 Sw w !sudo tee % > /dev/null

"-------------MAPPINGS--------------

vmap <C-c> "+y
nmap <C-a> ggVG
nmap <C-v> "+gp
vmap <C-v> "+gp
imap <C-v> <esc><C-v>a
nnoremap <C-b> <C-v>
imap <C-f> {}<Left><Enter><Up><Esc>o

nnoremap <C-h> <C-W>h
nnoremap <C-j> <C-W>j
nnoremap <C-k> <C-W>k
nnoremap <C-l> <C-W>l

nnoremap + <C-w>+
nnoremap - <C-w>-
nnoremap < <C-w><
nnoremap > <C-w>>

"-------------COMPETITIVE PROGRAMMING STUFF--------------

function! Setup()
    vs $HOME/VimProject/source.cpp
    silent only!
    silent tabonly!
    vs $HOME/VimProject/input.txt
    sp $HOME/VimProject/output.txt
    tabnew $HOME/VimProject/CompileMessage.txt
    tabfirst
    silent execute "normal \<C-w>h\<C-w>k"
    silent execute "normal \<C-w>20>"
endfunction

function! SetupBrute()
    call Setup()
    tabnew $HOME/VimProject/brute/generate.cpp
    tabnew $HOME/VimProject/brute/testsource.cpp
    vs $HOME/VimProject/brute/output_test.txt
    silent execute "normal \<C-w>h\<C-w>k"
    silent execute "normal \<C-w>20>"
    tabfirst
    silent execute "normal \<C-w>h\<C-w>k"
endfunction

function! ClearThis()
    if has('unix')
        w | silent !cp $HOME/VimProject/templates/core.cpp % &
    endif
    if has('win32')
        w | silent !copy \%userprofile\%\\VimProject\\templates\\core.cpp %
    endif
    redraw!
endfunction

function! StartBrute()
    wa
    !$HOME/VimProject/brute/script.sh
endfunction

func Library()
    tabnew | Ex $HOME/VimProject/templates
endfunction

command! ClearThis call ClearThis()
command! Setup call Setup()
command! SetupBrute call SetupBrute()
command! StartBrute call StartBrute()
command! Library call Library()

let local = "$HOME/VimProject/"
let messg = local."CompileMessage.txt"
let flags = "-D_MY -Wall -Wextra -Wfloat-conversion -Wconversion -Wshadow -Wno-unused-result -std=c++17"
"-fsanitize=address

function! CompRun()
    wa
    !g++ -D_MY -Wall -Wextra -Wfloat-conversion -Wconversion -Wshadow -Wno-unused-result -std=c++17 -O2 % -o %:r 2> $HOME/VimProject/CompileMessage.txt && echo SUCCESS && %:r || echo FAIL
endfunction
command! CompRun call CompRun()

"nnoremap <silent> <F5> :wa<CR><C-w>h<C-w>k :execute "!g++ ".flags." -O2 % -o %:r 2> ".messg." && echo SUCCESS && %:r \|\| echo FAIL" <CR>
"nnoremap <silent> <F6> :wa<CR><C-w>h<C-w>k :execute "!g++ ".flags." -O0 -g % -o %:r 2> ".messg." && echo SUCCESS && gdb %:r \|\| echo FAIL" <CR>
"nnoremap <silent> <F7> :wa<CR>:!python3 %<CR>


"-------------LATEX--------------

let g:tex_flavor = 'latex'

let g:vimtex_view_general_viewer = 'mupdf'
"let g:vimtex_view_general_options
"    \ = '-reuse-instance -forward-search @tex @line @pdf'
"let g:vimtex_view_general_options_latexmk = '-reuse-instance'

func SpellCheckRu()
    set spell spelllang=ru
endfunction

func SpellCheckEng()
    set spell spelllang=en
endfunction


set langmap=ФИСВУАПРШОЛДЬТЩЗЙКЫЕГМЦЧНЯ;ABCDEFGHIJKLMNOPQRSTUVWXYZ,фисвуапршолдьтщзйкыегмцчня;abcdefghijklmnopqrstuvwxyz
"autocmd FileType cpp,tex EnableXkbSwitch

"let g:XkbSwitchLib = '/usr/local/lib/libg3kbswitch.so'
"let g:XkbSwitchLib = "/path/to/libxkbswitch.so"
"echo libcall(g:XkbSwitchLib, 'Xkb_Switch_getXkbLayout', '')
"call libcall(g:XkbSwitchLib, 'Xkb_Switch_setXkbLayout', 'us')


autocmd filetype tex nnoremap j gj
autocmd filetype tex nnoremap k gk
autocmd filetype tex vnoremap j gj
autocmd filetype tex vnoremap k gk
autocmd filetype tex nnoremap о gj
autocmd filetype tex nnoremap л gk
autocmd filetype tex vnoremap о gj
autocmd filetype tex vnoremap л gk
autocmd filetype tex vnoremap <Up> g<Up>
autocmd filetype tex vnoremap <Down> g<Down>
autocmd filetype tex nnoremap <Up> g<Up>
autocmd filetype tex nnoremap <Down> g<Down> 

autocmd filetype tex inoremap ;;  <Esc>/<++><Enter>3xr :noh<Enter>i
autocmd filetype tex inoremap ;eq \begin{equation}<Enter>\end{equation}<Esc>ko
autocmd filetype tex inoremap ;tab \begin{tabular}<Enter>\end{tabular}<Esc>ko
autocmd filetype tex inoremap ;fr \frac{ }{<++>}<++><Esc>11hi

