const fs = require('fs');

var contents = fs.readFileSync(__dirname + '/contents.txt', {encoding: 'utf8'});

contents =contents.replace(/\\/gm, "\\\\")
contents = contents.replace(/"/g, "\\\"");
contents = contents.replace(/\r?\n/gm, "\\n");

fs.writeFileSync(__dirname + '/output.txt', contents, { encoding: 'utf8' });

