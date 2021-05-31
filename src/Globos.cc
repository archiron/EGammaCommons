
#include "DQMOffline/EGamma/interface/Globos.h"

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

Globos::Globos(const edm::ParameterSet &conf)
    : histoNamesReady(false), bookPrefix_("ele"), bookIndex_(0) {
  verbosity_ = conf.getUntrackedParameter<int>("Verbosity");
  finalStep_ = conf.getParameter<std::string>("FinalStep");
  inputFile_ = conf.getParameter<std::string>("InputFile");
  outputFile_ = conf.getParameter<std::string>("OutputFile");
  inputInternalPath_ = conf.getParameter<std::string>("InputFolderName");
  outputInternalPath_ = conf.getParameter<std::string>("OutputFolderName");
}

Globos::~Globos() {}

void Globos::setBookPrefix(const std::string &prefix) { bookPrefix_ = prefix; }

void Globos::setBookIndex(short index) { bookIndex_ = index; }

void Globos::setBookEfficiencyFlag(const bool &eff_flag) { bookEfficiencyFlag_ = eff_flag; }

void Globos::setBookStatOverflowFlag(const bool &statOverflow_flag) {
  bookStatOverflowFlag_ = statOverflow_flag;
}

// Common features for ElectronDqmAnalyzerBase/ElectronDqmHarvesterBase
Globos::MonitorElement *Globos::bookH1(DQMStore::IBooker &iBooker,
                                                                         const std::string &name,
                                                                         const std::string &title,
                                                                         int nchX,
                                                                         double lowX,
                                                                         double highX,
                                                                         const std::string &titleX,
                                                                         const std::string &titleY,
                                                                         Option_t *option) {
  iBooker.setCurrentFolder(outputInternalPath_);
  MonitorElement *me = iBooker.book1D(newName(name), title, nchX, lowX, highX);
  if (!titleX.empty()) {
    me->setAxisTitle(titleX);
  }
  if (!titleY.empty()) {
    me->setAxisTitle(titleY, 2);
    //me->getTH1F()->GetYaxis()->SetTitle(titleY.c_str());
  }
  if (TString(option) != "") {
    me->setOption(option);
  }
  if (bookStatOverflowFlag_) {
    me->setStatOverflows(kTRUE);
  }
  return me;
}

Globos::MonitorElement *Globos::bookH1withSumw2(DQMStore::IBooker &iBooker,
                                                                                  const std::string &name,
                                                                                  const std::string &title,
                                                                                  int nchX,
                                                                                  double lowX,
                                                                                  double highX,
                                                                                  const std::string &titleX,
                                                                                  const std::string &titleY,
                                                                                  Option_t *option) {
  iBooker.setCurrentFolder(outputInternalPath_);
  MonitorElement *me = iBooker.book1D(newName(name), title, nchX, lowX, highX);
  if (me->getTH1F()->GetSumw2N() == 0)
    me->enableSumw2();
  if (!titleX.empty()) {
    me->setAxisTitle(titleX);
  }
  if (!titleY.empty()) {
    me->setAxisTitle(titleY, 2);
    //me->getTH1F()->GetYaxis()->SetTitle(titleY.c_str());
  }
  if (TString(option) != "") {
    me->setOption(option);
  }
  if (bookStatOverflowFlag_) {
    me->setStatOverflows(kTRUE);
  }
  return me;
}

Globos::MonitorElement *Globos::bookH2(DQMStore::IBooker &iBooker,
                                                                           const std::string &name,
                                                                           const std::string &title,
                                                                           int nchX,
                                                                           double lowX,
                                                                           double highX,
                                                                           int nchY,
                                                                           double lowY,
                                                                           double highY,
                                                                           const std::string &titleX,
                                                                           const std::string &titleY,
                                                                           Option_t *option) {
  iBooker.setCurrentFolder(outputInternalPath_);
  MonitorElement *me = iBooker.book2D(newName(name), title, nchX, lowX, highX, nchY, lowY, highY);
  if (!titleX.empty()) {
    me->setAxisTitle(titleX);
  }
  if (!titleY.empty()) {
    me->setAxisTitle(titleY, 2);
    //me->getTH2F()->GetYaxis()->SetTitle(titleY.c_str());
  }
  if (TString(option) != "") {
    me->setOption(option);
  }
  if (bookStatOverflowFlag_) {
    me->getTH1F()->StatOverflows(kTRUE);
  }
  return me;
}

Globos::MonitorElement *Globos::bookH2withSumw2(DQMStore::IBooker &iBooker,
                                                                                    const std::string &name,
                                                                                    const std::string &title,
                                                                                    int nchX,
                                                                                    double lowX,
                                                                                    double highX,
                                                                                    int nchY,
                                                                                    double lowY,
                                                                                    double highY,
                                                                                    const std::string &titleX,
                                                                                    const std::string &titleY,
                                                                                    Option_t *option) {
  iBooker.setCurrentFolder(outputInternalPath_);
  MonitorElement *me = iBooker.book2D(newName(name), title, nchX, lowX, highX, nchY, lowY, highY);
  me->enableSumw2();
  if (!titleX.empty()) {
    me->setAxisTitle(titleX);
  }
  if (!titleY.empty()) {
    me->setAxisTitle(titleY, 2);
    //me->getTH2F()->GetYaxis()->SetTitle(titleY.c_str());
  }
  if (TString(option) != "") {
    me->setOption(option);
  }
  if (bookStatOverflowFlag_) {
    me->getTH1F()->StatOverflows(kTRUE);
  }
  return me;
}

Globos::MonitorElement *Globos::bookP1(DQMStore::IBooker &iBooker,
                                                                           const std::string &name,
                                                                           const std::string &title,
                                                                           int nchX,
                                                                           double lowX,
                                                                           double highX,
                                                                           double lowY,
                                                                           double highY,
                                                                           const std::string &titleX,
                                                                           const std::string &titleY,
                                                                           Option_t *option) {
  iBooker.setCurrentFolder(outputInternalPath_);
  MonitorElement *me = iBooker.bookProfile(newName(name), title, nchX, lowX, highX, lowY, highY, " ");
  if (!titleX.empty()) {
    me->getTProfile()->GetXaxis()->SetTitle(titleX.c_str());
  }
  if (!titleY.empty()) {
    me->setAxisTitle(titleY, 2);
    //me->getTProfile()->GetYaxis()->SetTitle(titleY.c_str());
  }
  if (TString(option) != "") {
    me->getTProfile()->SetOption(option);
  }
  if (bookStatOverflowFlag_) {
    me->getTH1F()->StatOverflows(kTRUE);
  }
  return me;
}

std::string Globos::newName(const std::string &name) {
  if (bookPrefix_.empty()) {
    return name;
  }
  std::ostringstream oss;
  oss << bookPrefix_;
  if (bookIndex_ >= 0) {
    oss << bookIndex_++;
  }
  oss << "_" << name;
  return oss.str();
}

// Features for ElectronDqmHarvesterBase

