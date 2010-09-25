lua-inih — bindings for inih, simple .INI file parser
=====================================================

See the copyright information in the file named `COPYRIGHT`.

More on inih: http://code.google.com/p/inih/

Note
----

Consider storing your data in .lua files.
Use lua-inih to convert your legacy .INI data to .lua.

Functions
---------

### inih.parse

`inih.parse(filename : string, callback : function) : true / nil, error_message`

Parse .INI file in `filename`, calling `callback` function for
each 'name = value' pair.

Default section name is "" (empty string).

Callback signature:

    callback(
        section : string,
        name : string,
        value : string
      ) : true / nil, error_message

Example:

    local inih = require 'inih'

    local data = { }

    assert(inih.parse('myfile.ini', function(section, name, value)
      data[section] = result[section] or { }
      data[section][name] = value

      return true -- continue parsing
    end))
