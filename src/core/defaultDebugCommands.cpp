#include "defaultDebugCommands.hpp"
#include "zDebug.hpp"

void addDefaultDebugFeatures(DebugManager *manager) {
  manager->addDebugFeature(new ShowSizes());
  manager->addDebugFeature(new ClearCommand());
  manager->addDebugFeature(new ExitCommand());
  manager->addDebugFeature(new AlwaysDraw());
}
