
#ifndef ElectronDqmAnalyzerBase_h
#define ElectronDqmAnalyzerBase_h

#include "DQMOffline/EGamma/interface/Globos.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <Rtypes.h>
#include <string>
#include <vector>

//DQM
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DQMServices/Core/interface/DQMEDAnalyzer.h"
#include "DQMServices/Core/interface/DQMStore.h"

namespace edab {
  struct Empty {};
}  // namespace edab
class ElectronDqmAnalyzerBase : public DQMEDAnalyzer, public Globos {
public:
  typedef Globos::DQMStore DQMStore;
  typedef Globos::MonitorElement MonitorElement;

protected:
  explicit ElectronDqmAnalyzerBase(const edm::ParameterSet &conf);
  ~ElectronDqmAnalyzerBase() override;

  // specific implementation of EDAnalyzer
  void bookHistograms(DQMStore::IBooker &, edm::Run const &, edm::EventSetup const &) override;

  // interface to implement in derived classes
  void analyze(const edm::Event &e, const edm::EventSetup &c) override {}

  // utility methods

/*  MonitorElement *cloneH1(DQMStore::IBooker &iBooker,
                          const std::string &name,
                          MonitorElement *original,
                          const std::string &title = "");

  MonitorElement *cloneH1(DQMStore::IBooker &iBooker,
                          const std::string &name,
                          const std::string &original,
                          const std::string &title = "");*/

private:
  //int verbosity_;
  //bool histoNamesReady;
  //std::string finalStep_;
  //std::string inputFile_;
  //std::string outputFile_;
  //std::string inputInternalPath_;
  //std::string outputInternalPath_;

  //std::vector<std::string> histoNames_;
};

#endif
