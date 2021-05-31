
#include "DQMOffline/EGamma/interface/ElectronDqmAnalyzerBase.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "TMath.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH1I.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TTree.h"
#include <iostream>
#include <algorithm>
#include <sstream>

ElectronDqmAnalyzerBase::ElectronDqmAnalyzerBase(const edm::ParameterSet &conf)
    : Globos(conf) {
  //verbosity_ = conf.getUntrackedParameter<int>("Verbosity");
  //finalStep_ = conf.getParameter<std::string>("FinalStep");
  //inputFile_ = conf.getParameter<std::string>("InputFile");
  //outputFile_ = conf.getParameter<std::string>("OutputFile");
  //inputInternalPath_ = conf.getParameter<std::string>("InputFolderName");
  //outputInternalPath_ = conf.getParameter<std::string>("OutputFolderName");
}

ElectronDqmAnalyzerBase::~ElectronDqmAnalyzerBase() {}

void ElectronDqmAnalyzerBase::bookHistograms(DQMStore::IBooker &ibooker_, edm::Run const &, edm::EventSetup const &) {
  edm::LogInfo("DQMAnalyzeBase::bookHistograms") << std::endl;
}



