"
" Mapping
"
let mapleader=','
function! Mapmap(lhs, rhs)
  execute 'map '.a:lhs.' '.a:rhs
  execute 'imap '.a:lhs.' <Esc>'.a:rhs
endfunction
" Cursor
noremap a h
noremap t j
noremap i k
noremap n l
noremap A ^
noremap T <C-d>
noremap I <C-u>
noremap N $
noremap x b
noremap X B
noremap b w
noremap B W
" Mode
noremap e i
noremap E I
noremap r a
noremap R A
noremap s v
noremap S V
noremap l o
noremap L O
" Operation
noremap f c
noremap F C
noremap u d
noremap U D
noremap c y
noremap c y
" Etc
noremap m @
noremap M q
noremap w :write<CR>
noremap h :noh<CR>
noremap H <Plug>(YCMHover)
noremap o .
noremap O R
noremap z za
noremap Z zR
noremap k n
noremap K N
noremap j :join!<CR>
noremap J :.-1join!<CR>
noremap d "
noremap D :registers<CR>
noremap q u
noremap Q <C-r>
noremap v :call CycleList('l', 'n')<CR>
noremap V :call CycleList('l', 'p')<CR>
noremap y g;
noremap Y g,
noremap <Space> o<Esc>
noremap <BackSpace> X
noremap ( [(
noremap ) ])
noremap { [{
noremap } ]}
noremap ; %
noremap + <C-a>
noremap - <C-x>

" Cursor
call Mapmap('<Leader><Left>',  '<C-w>h')
call Mapmap('<Leader><Right>', '<C-w>l')
call Mapmap('<Leader><Up>',    '<C-w>k')
call Mapmap('<Leader><Down>',  '<C-w>j')
call Mapmap('<PageUp>',        '<C-b>')
call Mapmap('<PageDown>',      '<C-f>')
" Window
call Mapmap('<Leader>w', ':wqall<CR>')
call Mapmap('<Leader>C', '<C-w>c')
call Mapmap('<Leader>Z', ':vsplit<CR>')
call Mapmap('<Leader>z', ':split<CR>')
" Buffer
call Mapmap('<Leader>c', ':call CloseBuf()<CR>')
call Mapmap('<Leader>s', ':bprevious<CR>')
call Mapmap('<Leader>r', ':bnext<CR>')
" Sizing
call Mapmap('<Leader>+', '<C-w>5+')
call Mapmap('<Leader>-', '<C-w>5-')
call Mapmap('<Leader><', '<C-w>5<')
call Mapmap('<Leader>>', '<C-w>5>')
call Mapmap('<Leader>=', '<C-w>=')
call Mapmap('<Leader>_', '<C-w>_')
call Mapmap('<Leader>\|', '<C-w>\|')
" List
call Mapmap('<Leader>t', ':call ToggleList("l")<CR>')
call Mapmap('<Leader>i', ':call ToggleList("c")<CR>')
call Mapmap('<Leader>v', ':call CycleList("c","n")<CR>')
call Mapmap('<Leader>V', ':call CycleList("c","p")<CR>')
" YCM
call Mapmap('<Leader>p', ':YcmCompleter GoToAlternateFile<CR>')
call Mapmap('<Leader>G', ':YcmCompleter GoToReferences<CR>:call AfterYcm()<CR>')
call Mapmap('<Leader>g', ':YcmCompleter GoTo<CR>')
call Mapmap('<Leader>A', '<Plug>(YCMFindSymbolInWorkspace)')
" Nerdtree
call Mapmap('<Leader>a', ':NERDTreeToggle<CR>')
let g:NERDTreeMenuUp='i'
let g:NERDTreeMenuDown='t'
let g:NERDTreeMapRefresh='a'
let g:NERDTreeMapCustomOpen='n'
" Tagbar
call Mapmap('<Leader>n', ':TagbarToggle<CR>')
let g:tagbar_map_togglecaseinsensitive = ""
let g:tagbar_map_togglesort = ""
let g:tagbar_map_togglepause = ""
let g:tagbar_map_jump = "a"
" Etc
call Mapmap('<Leader>y', '<C-o>')
call Mapmap('<Leader>Y', '<C-i>')
