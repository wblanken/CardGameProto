#include "CardDataLoader.h"

#include "Styling/SlateStyleRegistry.h"

#define LOCTEXT_NAMESPACE "FCardDataLoaderModule"

DEFINE_LOG_CATEGORY(LogCardDataLoader);

void FCardDataLoaderModule::StartupModule()
{
}

void FCardDataLoaderModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FCardDataLoaderModule, CardDataLoader)