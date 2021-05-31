
#include "DQMOffline/EGamma/interface/ElectronDqmHarvesterBase.h"
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

ElectronDqmHarvesterBase::ElectronDqmHarvesterBase(const edm::ParameterSet &conf)
    : Globos(conf), finalDone_(false) {
}

ElectronDqmHarvesterBase::~ElectronDqmHarvesterBase() {}

/*const std::string *ElectronDqmHarvesterBase::find(DQMStore::IGetter &iGetter, const std::string &name) {
  if (!histoNamesReady) {
    histoNamesReady = true;
    histoNames_ = iGetter.getMEs();
  }
  std::vector<const std::string *> res;
  std::size_t nsize = name.size();

  for (const auto &histoName : histoNames_) {
    std::size_t lsize = histoName.size();
    if ((lsize >= nsize) && (histoName.find(name) == (lsize - nsize))) {
      res.push_back(&histoName);
    }
  }
  if (res.empty()) {
    std::ostringstream oss;
    oss << "Histogram " << name << " not found in " << outputInternalPath_;
    char sep = ':';
    for (auto const &histoName : histoNames_) {
      oss << sep << ' ' << histoName;
      sep = ',';
    }
    oss << '.';
    edm::LogWarning("ElectronDqmHarvesterBase::find") << oss.str();
    return nullptr;
  } else if (res.size() > 1) {
    std::ostringstream oss;
    oss << "Ambiguous histograms for " << name << " in " << outputInternalPath_;
    char sep = ':';
    for (auto const resItr : res) {
      oss << sep << ' ' << *resItr;
      sep = ',';
    }
    oss << '.';
    edm::LogWarning("ElectronDqmHarvesterBase::find") << oss.str();
    return nullptr;
  }
  return res[0];
}*/

void ElectronDqmHarvesterBase::beginJob() {}

void ElectronDqmHarvesterBase::dqmEndLuminosityBlock(DQMStore::IBooker &iBooker,
                                                     DQMStore::IGetter &iGetter,
                                                     edm::LuminosityBlock const &,
                                                     edm::EventSetup const &) {
  if (finalStep_ == "AtLumiEnd") {
    if (finalDone_) {
      edm::LogWarning("ElectronDqmHarvesterBase::endLuminosityBlock") << "finalize() already called";
    }
    iBooker.setCurrentFolder(outputInternalPath_);
    finalDone_ = true;
  }
}

void ElectronDqmHarvesterBase::dqmEndJob(DQMStore::IBooker &iBooker, DQMStore::IGetter &iGetter) {
  if (finalStep_ == "AtJobEnd") {
    if (finalDone_) {
      edm::LogWarning("ElectronDqmHarvesterBase::dqmEndJob") << "finalize() already called";
    }
    iBooker.setCurrentFolder(outputInternalPath_);
    finalDone_ = true;
  }
  iBooker.setCurrentFolder(outputInternalPath_);
  finalize(iBooker, iGetter);
}

/*ElectronDqmHarvesterBase::MonitorElement *ElectronDqmHarvesterBase::get(DQMStore::IGetter &iGetter,
                                                                        const std::string &name) {
  const std::string *fullName = find(iGetter, name);
  if (fullName) {
    return iGetter.get(inputInternalPath_ + "/" + *fullName);
  } else {
    return nullptr;
  }
}*/

void ElectronDqmHarvesterBase::remove(DQMStore::IBooker &iBooker, DQMStore::IGetter &iGetter, const std::string &name) {
  // TODO: remove no longer supported in DQMStore.
}

/*ElectronDqmHarvesterBase::MonitorElement *ElectronDqmHarvesterBase::bookH1andDivide(DQMStore::IBooker &iBooker,
                                                                                    DQMStore::IGetter &iGetter,
                                                                                    const std::string &name,
                                                                                    const std::string &num,
                                                                                    const std::string &denom,
                                                                                    const std::string &titleX,
                                                                                    const std::string &titleY,
                                                                                    const std::string &title) {
  return bookH1andDivide(iBooker, iGetter, name, get(iGetter, num), get(iGetter, denom), titleX, titleY, title);
}

ElectronDqmHarvesterBase::MonitorElement *ElectronDqmHarvesterBase::bookH1andDivide(DQMStore::IBooker &iBooker,
                                                                                    DQMStore::IGetter &iGetter,
                                                                                    const std::string &name,
                                                                                    MonitorElement *num,
                                                                                    MonitorElement *denom,
                                                                                    const std::string &titleX,
                                                                                    const std::string &titleY,
                                                                                    const std::string &title) {
  if ((!num) || (!denom))
    return nullptr;
  iBooker.setCurrentFolder(outputInternalPath_);
  std::string name2 = newName(name);
  TH1F *h_temp = (TH1F *)num->getTH1F()->Clone(name2.c_str());
  h_temp->Reset();
  h_temp->Divide(num->getTH1(), denom->getTH1(), 1, 1, "b");
  h_temp->GetXaxis()->SetTitle(titleX.c_str());
  h_temp->GetYaxis()->SetTitle(titleY.c_str());
  if (!title.empty()) {
    h_temp->SetTitle(title.c_str());
  }
  //if (verbosity_ > 0) {
  if (verbosity() > 0) {
    h_temp->Print();
  }
  MonitorElement *me = iBooker.book1D(name2, h_temp);
  if (bookEfficiencyFlag_) {
  //if (bookEfficiencyFlag()) {
    me->setEfficiencyFlag();
  }
  delete h_temp;
  return me;
}*/

/*ElectronDqmHarvesterBase::MonitorElement *ElectronDqmHarvesterBase::bookH2andDivide(DQMStore::IBooker &iBooker,
                                                                                    DQMStore::IGetter &iGetter,
                                                                                    const std::string &name,
                                                                                    const std::string &num,
                                                                                    const std::string &denom,
                                                                                    const std::string &titleX,
                                                                                    const std::string &titleY,
                                                                                    const std::string &title) {
  return bookH2andDivide(iBooker, iGetter, name, get(iGetter, num), get(iGetter, denom), titleX, titleY, title);
}

ElectronDqmHarvesterBase::MonitorElement *ElectronDqmHarvesterBase::bookH2andDivide(DQMStore::IBooker &iBooker,
                                                                                    DQMStore::IGetter &iGetter,
                                                                                    const std::string &name,
                                                                                    MonitorElement *num,
                                                                                    MonitorElement *denom,
                                                                                    const std::string &titleX,
                                                                                    const std::string &titleY,
                                                                                    const std::string &title) {
  if ((!num) || (!denom))
    return nullptr;
  iBooker.setCurrentFolder(outputInternalPath_);
  std::string name2 = newName(name);
  TH2F *h_temp = (TH2F *)num->getTH2F()->Clone(name2.c_str());
  h_temp->Reset();
  h_temp->Divide(num->getTH1(), denom->getTH1(), 1, 1, "b");
  h_temp->GetXaxis()->SetTitle(titleX.c_str());
  h_temp->GetYaxis()->SetTitle(titleY.c_str());
  if (!title.empty()) {
    h_temp->SetTitle(title.c_str());
  }
  //if (verbosity_ > 0) {
  if (verbosity() > 0) {
    h_temp->Print();
  }
  MonitorElement *me = iBooker.book2D(name2, h_temp);
  if (bookEfficiencyFlag_) {
  //if (bookEfficiencyFlag()) {
    me->setEfficiencyFlag();
  }
  delete h_temp;
  return me;
}*/

ElectronDqmHarvesterBase::MonitorElement *ElectronDqmHarvesterBase::cloneH1(DQMStore::IBooker &iBooker,
                                                                            DQMStore::IGetter &iGetter,
                                                                            const std::string &clone,
                                                                            const std::string &original,
                                                                            const std::string &title) {
  return cloneH1(iBooker, iGetter, clone, get(iGetter, original), title);
}

ElectronDqmHarvesterBase::MonitorElement *ElectronDqmHarvesterBase::cloneH1(DQMStore::IBooker &iBooker,
                                                                            DQMStore::IGetter &iGetter,
                                                                            const std::string &name,
                                                                            MonitorElement *original,
                                                                            const std::string &title) {
  if (!original)
    return nullptr;
  iBooker.setCurrentFolder(outputInternalPath_);
  std::string name2 = newName(name);
  TH1F *h_temp = (TH1F *)original->getTH1F()->Clone(name2.c_str());
  h_temp->Reset();
  if (!title.empty()) {
    h_temp->SetTitle(title.c_str());
  }
  MonitorElement *me = iBooker.book1D(name2, h_temp);
  delete h_temp;
  return me;
}

ElectronDqmHarvesterBase::MonitorElement *ElectronDqmHarvesterBase::profileX(DQMStore::IBooker &iBooker,
                                                                             DQMStore::IGetter &iGetter,
                                                                             const std::string &me2d,
                                                                             const std::string &title,
                                                                             const std::string &titleX,
                                                                             const std::string &titleY,
                                                                             Double_t minimum,
                                                                             Double_t maximum) {
  return profileX(iBooker, iGetter, get(iGetter, me2d), title, titleX, titleY, minimum, maximum);
}

ElectronDqmHarvesterBase::MonitorElement *ElectronDqmHarvesterBase::profileX(DQMStore::IBooker &iBooker,
                                                                             DQMStore::IGetter &iGetter,
                                                                             MonitorElement *me2d,
                                                                             const std::string &title,
                                                                             const std::string &titleX,
                                                                             const std::string &titleY,
                                                                             Double_t minimum,
                                                                             Double_t maximum) {
  iBooker.setCurrentFolder(outputInternalPath_);
  std::string name2 = me2d->getName() + "_pfx";
  TProfile *p1_temp = me2d->getTH2F()->ProfileX();
  if (!title.empty()) {
    p1_temp->SetTitle(title.c_str());
  }
  if (!titleX.empty()) {
    p1_temp->GetXaxis()->SetTitle(titleX.c_str());
  }
  if (!titleY.empty()) {
    p1_temp->GetYaxis()->SetTitle(titleY.c_str());
  }
  if (minimum != -1111) {
    p1_temp->SetMinimum(minimum);
  }
  if (maximum != -1111) {
    p1_temp->SetMaximum(maximum);
  }
  MonitorElement *me = iBooker.bookProfile(name2, p1_temp);
  delete p1_temp;
  return me;
}

ElectronDqmHarvesterBase::MonitorElement *ElectronDqmHarvesterBase::profileY(DQMStore::IBooker &iBooker,
                                                                             DQMStore::IGetter &iGetter,
                                                                             const std::string &me2d,
                                                                             const std::string &title,
                                                                             const std::string &titleX,
                                                                             const std::string &titleY,
                                                                             Double_t minimum,
                                                                             Double_t maximum) {
  return profileY(iBooker, iGetter, get(iGetter, me2d), title, titleX, titleY, minimum, maximum);
}

ElectronDqmHarvesterBase::MonitorElement *ElectronDqmHarvesterBase::profileY(DQMStore::IBooker &iBooker,
                                                                             DQMStore::IGetter &iGetter,
                                                                             MonitorElement *me2d,
                                                                             const std::string &title,
                                                                             const std::string &titleX,
                                                                             const std::string &titleY,
                                                                             Double_t minimum,
                                                                             Double_t maximum) {
  iBooker.setCurrentFolder(outputInternalPath_);
  std::string name2 = me2d->getName() + "_pfy";
  TProfile *p1_temp = me2d->getTH2F()->ProfileY();
  if (!title.empty()) {
    p1_temp->SetTitle(title.c_str());
  }
  if (!titleX.empty()) {
    p1_temp->GetXaxis()->SetTitle(titleX.c_str());
  }
  if (!titleY.empty()) {
    p1_temp->GetYaxis()->SetTitle(titleY.c_str());
  }
  if (minimum != -1111) {
    p1_temp->SetMinimum(minimum);
  }
  if (maximum != -1111) {
    p1_temp->SetMaximum(maximum);
  }
  MonitorElement *me = iBooker.bookProfile(name2, p1_temp);
  delete p1_temp;
  return me;
}

