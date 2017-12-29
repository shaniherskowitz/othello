#include "Command.h"

Command::Command(ServerGames *server1) { server = server1; }

Command::~Command() { ServerGames::deleteInstance(); }