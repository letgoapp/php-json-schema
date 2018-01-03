# Json Schema validator for PHP

This PHP extension is intended to validate [JSON documents](https://www.json.org)	 against a [JSON Schema](http://json-schema.org/) draft 04.

## Requirements

- GCC compiler
- [PHPCPP](http://www.php-cpp.com/documentation/install)

## How to build

Just run `make` that will create a json-schema.so which should be copied to the PHP extension directory and loaded in the PHP INI.

## API

### json\_schema\_validate(string $document, string $schema): bool

### json\_schema\_last\_error\_msg(): array