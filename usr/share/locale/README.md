# gettext locales

## extract template from source files (list in input.txt)

```bash
xgettext -d usr/share/locale -o template.pot --files-from=input.txt --directory="../../../src"
```

## create locale files from template

- LANG_CODE: code of language
- PO_NAME: name of the .po language file

```bash
msginit -l {LANG_CODE} -o {PO_NAME}.po -i template.pot
```

## create binary format that will be read by gettext in LC_MESSAGES folder

- LANG_CODE: code of language
- PO_NAME: name of the .po language file
- MO_NAME: name of the .mo file (the binary output file)

```bash
msgfmt -c -v -o {MO_NAME}.mo {PO_NAME}.po
cp {MO_NAME}.mo {LANG_CODE}/LC_MESSAGES
```

<hr>

```bash
# gettext locales
# extract template from source files (list in input.txt)
xgettext -d usr/share/locale -o template.pot --files-from=input.txt --directory="../../../src"


## create locale files from template

# - LANG_CODE: code of language
# - PO_NAME: name of the .po language file

msginit -l {LANG_CODE} -o {PO_NAME}.po -i template.pot

# create binary format that will be read by gettext in LC_MESSAGES folder

# - LANG_CODE: code of language
# - PO_NAME: name of the .po language file
# - MO_NAME: name of the .mo file (the binary output file)

msgfmt -c -v -o {MO_NAME}.mo {PO_NAME}.po
cp {MO_NAME}.mo {LANG_CODE}/LC_MESSAGES