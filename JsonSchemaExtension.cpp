#include <phpcpp.h>

#include <fstream>
#include <iostream>
#include <stdexcept>

#include <rapidjson/document.h>

#include <valijson/adapters/rapidjson_adapter.hpp>
#include <valijson/utils/rapidjson_utils.hpp>
#include <valijson/schema.hpp>
#include <valijson/schema_parser.hpp>
#include <valijson/validation_results.hpp>
#include <valijson/validator.hpp>

using valijson::Schema;
using valijson::SchemaParser;
using valijson::Validator;
using valijson::ValidationResults;
using valijson::adapters::RapidJsonAdapter;

ValidationResults results;


bool validate(rapidjson::Document &targetDocument, rapidjson::Document &schemaDocument)
{
    Schema schema;
    SchemaParser parser;
    RapidJsonAdapter schemaDocumentAdapter(schemaDocument);
    try {
        parser.populateSchema(schemaDocumentAdapter, schema);
    } catch (std::exception &e) {
        Php::error << "Failed to parse schema: " << e.what() << std::flush;
        return false;
    }

    Validator validator(Validator::kWeakTypes);
    
    RapidJsonAdapter targetDocumentAdapter(targetDocument);
    if (!validator.validate(schema, targetDocumentAdapter, &results)) {
		return false;
	}
	
	return true;	
}

Php::Value jsonschema_validate(Php::Parameters &params)
{
    rapidjson::Document targetDocument;
	targetDocument.template Parse<0>(params[0]);
	if (targetDocument.HasParseError()) {
		Php::error << "Failed to load target document." << std::flush;
		return false;
    }
	
	rapidjson::Document schemaDocument;
    schemaDocument.template Parse<0>(params[1]);
    if (schemaDocument.HasParseError()) {
        Php::error << "Failed to load schema document." << std::flush;		
        return false;
    }
		
	return validate(targetDocument, schemaDocument);	
}

Php::Value jsonschema_last_error_msg()
{
	ValidationResults::Error error;
	unsigned int errorNum = 0;
	Php::Array messages;
	while (results.popError(error)) {
		std::string context;
		std::vector<std::string>::iterator itr = error.context.begin();
		for (; itr != error.context.end(); itr++) {
			context += *itr;
		}
		
		messages[errorNum] = error.description;
		errorNum++;
	}
	
	return messages;
}

extern "C" {

    PHPCPP_EXPORT void *get_module() 
    {
        static Php::Extension extension("json-schema", "0.1");

        extension.add<jsonschema_validate>("jsonschema_validate", {
			Php::ByVal("filename", Php::Type::String),
			Php::ByVal("schema", Php::Type::String)
		});
		
		extension.add<jsonschema_last_error_msg>("jsonschema_last_error_msg");

		return extension;
    }
}
