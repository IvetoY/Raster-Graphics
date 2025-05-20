#include "Undo.h"
#include "../Session/Session.h"

void Undo::apply(Session& session){
    session.undo();
}