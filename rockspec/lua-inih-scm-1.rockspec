package = "lua-inih"
version = "scm-1"
source = {
   url = "git://github.com/agladysh/lua-inih.git",
   branch = "master"
}
description = {
   summary = "Bindings for inih, simple .INI file parser",
   homepage = "http://github.com/agladysh/lua-inih",
   license = "MIT/X11",
   maintainer = "Alexander Gladysh <agladysh@gmail.com>"
}
dependencies = {
   "lua >= 5.1"
}
build = {
   type = "builtin",
   modules = {
      inih = {
         sources = {
            "src/lua-inih.c",
            "lib/inih/ini.c"
         },
         incdirs = {
            "src/",
            "lib/inih/"
         }
      }
   }
}
