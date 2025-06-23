#include "debugIntegration.hpp"

void addColliderDebugIntegration(EngineContext *ctx) {
  ctx->debugManager.addDebugFeature(new ColliderDebug());
}
