# Json Schema validator for PHP

This PHP extension is intended to validate [JSON documents](https://www.json.org)	 against a [JSON Schema](http://json-schema.org/) draft 04.

## Requirements

- GCC compiler
- C++ library for developing PHP extensions, [PHPCPP](http://www.php-cpp.com/documentation/install)
- Header-only C++ library, [valijson](https://github.com/tristanpenman/valijson)

## How to install

Run the following commands:

```
~# git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git
~# cd PHP-CPP
~# make
~# make install
~# cd ..
~# git clone https://github.com/softrog/php-json-schema.git
~# cd php-json-schema
~# git clone https://github.com/tristanpenman/valijson.git
~# make
~# make install
```

The extension should be copied into the PHP EXTENSION_DIR and ready to be loaded.

## API

### json\_schema\_validate(string $document, string $schema): bool

### json\_schema\_last\_error\_msg(): array