#include "Propertie.h"

Propertie::Propertie(Json::Value json)
{
	linkType = json["linkType"].asString();
	linkId = json["linkId"].asString();
}