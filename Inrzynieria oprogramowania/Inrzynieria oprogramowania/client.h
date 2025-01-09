#pragma once
#include"context.h"
#include "state.h"

/**
 * The client code.
 */
void ClientCode() {
    Context* context = new Context(1);
    
    context->Request1();
    context->Request2();
    delete context;
}