#include "Message.h"

Message::Message(std::string t) : text(t) {next = NULL;}

std::string Message::getText() {return text;}