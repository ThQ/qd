if version < 600
   syntax clear
elseif exists("b:current_syntax") && b:current_syntax == "sir"
   finish
endif

syn match      sirComment           "#.*$"
syn match      sirString            "\"[^\"]*\""
syn match      sirNumber             " -\=\d\+\(\.\d\+\)\="
syn match      sirMethod            "\s*[a-zA-Z]\+:[a-zA-Z_]\+"
syn match      sirHeapObject        " \$\d\+"
syn match      sirContent           ",\"[^\"]*\""
syn match      sirPreprocessor      "^\s*%%.*$"

if version >= 508 || !exists("did_sir_syntax_inits")
   if version < 508
      let did_sir_syntax_inits = 1
      command! -nargs=+ HiLink hi link <args>
   else
      command! -nargs=+ HiLink hi def link <args>
   endif

   HiLink sirString        String
   HiLink sirNumber        Number
   HiLink sirComment       Comment
   HiLink sirPreprocessor  Comment
   HiLink sirHeapObject    Identifier
   HiLink sirContent       PreCondit

   delcommand HiLink
endif

let b:current_syntax = "sir"

