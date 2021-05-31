
#ifndef ElectronDqmHarvesterBase_h
#define ElectronDqmHarvesterBase_h

#include "DQMOffline/EGamma/interface/Globos.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <Rtypes.h>
#include <string>
#include <vector>

//DQM
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DQMServices/Core/interface/DQMEDHarvester.h"
#include "DQMServices/Core/interface/DQMStore.h"

class ElectronDqmHarvesterBase : public DQMEDHarvester, public Globos {
public:
  typedef Globos::DQMStore DQMStore;
  typedef Globos::MonitorElement MonitorElement;

protected:
  explicit ElectronDqmHarvesterBase(const edm::ParameterSet &conf);
  ~ElectronDqmHarvesterBase() override;

  // specific implementation of EDAnalyzer
  void beginJob() override;  // prepare DQM, open input field if declared, and call book() below
  void dqmEndLuminosityBlock(DQMStore::IBooker &,
                             DQMStore::IGetter &,
                             edm::LuminosityBlock const &,
                             edm::EventSetup const &) override;       //performed in the endLumi
  void dqmEndJob(DQMStore::IBooker &, DQMStore::IGetter &) override;  //performed in the endJob

  // interface to implement in derived classes
  virtual void finalize(DQMStore::IBooker &iBooker,
                        DQMStore::IGetter &iGetter){};  //  override ;, const edm::Event& e, const edm::EventSetup & c

  // utility methods
  bool finalStepDone() { return finalDone_; }
  MonitorElement *get(DQMStore::IGetter &iGetter, const std::string &name);
  void remove(DQMStore::IBooker &iBooker, DQMStore::IGetter &iGetter, const std::string &name);

  MonitorElement *bookH1andDivide(DQMStore::IBooker &iBooker,
                                  DQMStore::IGetter &,
                                  const std::string &name,
                                  MonitorElement *num,
                                  MonitorElement *denom,
                                  const std::string &titleX,
                                  const std::string &titleY,
                                  const std::string &title = "");

  MonitorElement *bookH2andDivide(DQMStore::IBooker &iBooker,
                                  DQMStore::IGetter &,
                                  const std::string &name,
                                  MonitorElement *num,
                                  MonitorElement *denom,
                                  const std::string &titleX,
                                  const std::string &titleY,
                                  const std::string &title = "");

  MonitorElement *cloneH1(DQMStore::IBooker &iBooker,
                          DQMStore::IGetter &,
                          const std::string &name,
                          MonitorElement *original,
                          const std::string &title = "");

  MonitorElement *profileX(DQMStore::IBooker &iBooker,
                           DQMStore::IGetter &iGetter,
                           MonitorElement *me2d,
                           const std::string &title = "",
                           const std::string &titleX = "",
                           const std::string &titleY = "",
                           Double_t minimum = -1111,
                           Double_t maximum = -1111);

  MonitorElement *profileY(DQMStore::IBooker &iBooker,
                           DQMStore::IGetter &iGetter,
                           MonitorElement *me2d,
                           const std::string &title = "",
                           const std::string &titleX = "",
                           const std::string &titleY = "",
                           Double_t minimum = -1111,
                           Double_t maximum = -1111);

  MonitorElement *bookH1andDivide(DQMStore::IBooker &iBooker,
                                  DQMStore::IGetter &iGetter,
                                  const std::string &name,
                                  const std::string &num,
                                  const std::string &denom,
                                  const std::string &titleX,
                                  const std::string &titleY,
                                  const std::string &title = "");

  MonitorElement *bookH2andDivide(DQMStore::IBooker &iBooker,
                                  DQMStore::IGetter &,
                                  const std::string &name,
                                  const std::string &num,
                                  const std::string &denom,
                                  const std::string &titleX,
                                  const std::string &titleY,
                                  const std::string &title = "");

  MonitorElement *cloneH1(DQMStore::IBooker &iBooker,
                          DQMStore::IGetter &,
                          const std::string &name,
                          const std::string &original,
                          const std::string &title = "");

  MonitorElement *profileX(DQMStore::IBooker &iBooker,
                           DQMStore::IGetter &iGetter,
                           const std::string &me2d,
                           const std::string &title = "",
                           const std::string &titleX = "",
                           const std::string &titleY = "",
                           Double_t minimum = -1111,
                           Double_t maximum = -1111);

  MonitorElement *profileY(DQMStore::IBooker &iBooker,
                           DQMStore::IGetter &iGetter,
                           const std::string &me2d,
                           const std::string &title = "",
                           const std::string &titleX = "",
                           const std::string &titleY = "",
                           Double_t minimum = -1111,
                           Double_t maximum = -1111);

private:
  std::vector<std::string> histoNames_;
  bool finalDone_;

  // utility methods
  const std::string *find(DQMStore::IGetter &iGetter, const std::string &name);
};

#endif
