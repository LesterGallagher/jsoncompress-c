const fs = require('fs');

let cTemplate = fs.readFileSync(`${__dirname}/list.template.txt`).toString();
let hTemplate = fs.readFileSync(`${__dirname}/list.template.h.txt`).toString();

const wrapperType = process.argv[2].replace(/_t\s*\*$/, '*').replace(/\s*\*/g, '_ptr').replace(/_t$/, '');

const locals = {
    type: wrapperType,
    typeUnderscore: wrapperType.replace(/[- ]/g, '_'),
    typeHyphen: wrapperType.replace(/[_ ]/g, '-'),
    typeUpcase: (wrapperType || '').toUpperCase(),
    innerType: process.argv[2],
    innerTypeUnderscore: process.argv[2].replace(/[- ]/g, '_'),
    innerTypeHyphen: process.argv[2].replace(/[_ ]/g, '-'),
    innerTypeUpcase: (process.argv[2] || '').toUpperCase(),
};

cTemplate = cTemplate.replace(/\${(.+?)}/g, (match, name) => {
    return locals[name];
});

hTemplate = hTemplate.replace(/\${(.+?)}/g, (match, name) => {
    return locals[name];
});

const cFile = `${__dirname}/../${locals.typeHyphen}-list.c`;
const hFile = `${__dirname}/../${locals.typeHyphen}-list.h`;

if (fs.existsSync(cFile)) throw "File already exists";
if (fs.existsSync(hFile)) throw "File already exists";

fs.writeFileSync(cFile, cTemplate);
fs.writeFileSync(hFile, hTemplate);
