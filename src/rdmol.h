#include <emscripten/bind.h>
#include <string>
#include <vector>
#include <GraphMol/ROMol.h>
#include <GraphMol/RWMol.h>
#include <GraphMol/SmilesParse/SmilesParse.h>
#include <GraphMol/FileParsers/FileParsers.h>
#include <DataStructs/SparseBitVect.h>
#include <DataStructs/SparseIntVect.h>
#include <DataStructs/BitOps.h>
#include <GraphMol/Conformer.h>
#include <boost/cstdint.hpp>



using namespace std;
using namespace emscripten;
using RDKit::ROMol;
using RDKit::RWMol;

class Molecule
{
public:
    Molecule(RWMol *mol);
    
    ~Molecule();

    // paolo code testing of pi contact generator
    unsigned int enumNbrConjGrp( std::vector<unsigned int> &atomConjGrpIdx,  std::vector<unsigned int> &bondConjGrpIdx, std::map<unsigned int, std::vector<unsigned int> > &m);
    unsigned int picontacts();
    unsigned int getAtomCountRingBonds(int atomid);
    unsigned int getAtomHeavyValence(int atomid);
    unsigned int getAtomHeteroValence(int atomid);
    unsigned int getAtomValence(int atomid);




    double Similarity(const Molecule moltocompare, string similarityfunction,double a, double b);

    // canonical
    vector<unsigned int> CanonicalRankAtoms(bool breakTies, bool includeChirality, bool includeIsotopes);

    // SA score Peter Erl
    int getNumMacrocycles();
    int getNumSpiroAtoms();
    int getNumBridgeheadAtoms();
    vector<string> FindMolChiralCenters(bool includeUnassigned);
    
    // new fingerprints
    boost::uint32_t getAtomCode(int atomid);
    vector<int> getAtomPairFingerprint();
    vector<int> getHashedAtomPairFingerprint(int size, int atomid1, int atomid2);
    string getHashedAtomPairFingerprintAsBitVect(int size, int atomid1, int atomid2);



    string getRDKFP();
    string getMorganFP(unsigned int sizes,unsigned int lengths);
    vector<int> getMorganFP_GetOnBits(unsigned int sizes,unsigned int lengths);
    // const map<unsigned int,int> getMorganFP_getNonzeroElements(unsigned int sizes);
    vector<boost::uint32_t> getMorganUFPkeys(unsigned int sizes);

    map<boost::uint32_t, int> getMorganFP_getNonzeroElements(unsigned int sizes);
    vector<boost::uint32_t> getMorganFPlist(unsigned int sizes);
    // RDKit::SparseIntVect<boost::uint32_t>::StorageType getMorganFP_getNonzeroElements(unsigned int sizes);
    string getLayeredFP(unsigned int layer,unsigned int sizes,unsigned int lengths);
    string getMACCSFP();
    string getPatternFP();
    
    
    
    // 3D Force Field minimization
    vector<double> MMFFoptimizeMolecule();
    vector<double> MMFFoptimizeMolecule(int maxIters, string mmffVariant);
    vector<double> MMFFOptimizeMoleculeConfs(unsigned int numThreads,int maxIters, string mmffVariant);
    vector<double> UFFOptimizeMolecule();
    
    // generate 3D non optimized molecule
    int EmbedMolecule();
    int EmbedMolecule(unsigned int maxIterations,int seed);
    vector<int> EmbedMultipleConfs();
    vector<int> EmbedMultipleConfs(unsigned int numConfs, unsigned int maxIterations, int seed);
    
    
    
    // Pickle molecule representation
    string MolToBinary();
    
    
    
    string getPath();
    // string output in console
    string toSmiles();
    string toMolfile();
    // string sdwritefile(string filename);
    // int writefile(string filename, string data);
    // int readfile(string filename);
    
    // string sdreadfile(string filename);
    string sdwriteConfs();
    
    
    // indexedDB storage
    // void save(string path, string data);
    // string load(string path);
    // int nodereadwrite();
    // int nodereadwritewithdata(string path, string data);
    
    // input file
    
    
    // output file
    
    
    // Drawing molecule
    unsigned int compute2DCoords();
    string Drawing2D();
    vector<float> getAtomsPos2D();
    // similarity
    double TanimotoSimilarityfromSmile (string smilesref);
    double DiceSimilarityfromSmile (string smilesref);
    double TverskySimilarityfromSmile( string smilesref,double a, double b);
    
    
    int findSSSRnumber();
    map<int, string>  findSSSR();

    // return matrix ... vector<double> AlignMolConformersRMSlist();

    void AlignMolConformers();

    vector<double> getConformersRMS(unsigned int confId1,unsigned int confId2,unsigned int maxIters);

    double AlignMol(string smilesref);

    
    
    
    // molecule manipulation & cleaning, ...
    void addHs();
    void removeHs();
    void sanitizeMol();
    void cleanUp();
    void Kekulize();
    
    
    
    // descriptors
    int getMW();
    double ExactMW();
    string Formula();
    double Chi0v();
    double Chi1v();
    double Chi2v();
    double Chi3v();
    double Chi4v();
    double ChiNv(unsigned int N);

    double Chi0n();
    double Chi1n();
    double Chi2n();
    double Chi3n();
    double Chi4n();
    double ChiNn(unsigned int N);

    double HallKierAlpha();
    double Kappa1();
    double Kappa2();
    double Kappa3();
    vector<double>  logp_mr();
    
    vector<double> getCrippenAtomContribs();

    
    unsigned int LipinskiHBA();
    unsigned int LipinskiHBD();
    unsigned int NumRotatableBonds();
    unsigned int NumHBD();
    unsigned int NumHBA();
    unsigned int NumHeteroatoms();
    unsigned int NumAmideBonds();
    double FractionCSP3();
    unsigned int NumRings();
    unsigned int NumAromaticRings();
    unsigned int NumAliphaticRings();
    unsigned int NumSaturatedRings();
    unsigned int NumHeterocycles();
    unsigned int NumAromaticHeterocycles();
    unsigned int NumAromaticCarbocycles ();
    unsigned int NumSaturatedHeterocycles();
    unsigned int NumSaturatedCarbocycles();
    unsigned int NumAliphaticHeterocycles();
    unsigned int NumAliphaticCarbocycles();
    double LabuteASA();
    vector<double> getASAContribs();

    double TPSA();
    vector<double>  getTPSAAtomContribs();

    vector<double> SlogP_VSA();
    vector<double> SMR_VSA();
    vector<double> PEO_VSA();
    vector<unsigned int> MQNs();

    void computeGasteigerCharges();


    vector<int> GetSubstructMatches(string smilesref);
    int GetSubstructMatchesNumber(string smilesref);

    bool HasSubstructMatchStr(string smilesref);
    /// get & set & has properties
    string getProp(string key);
    string getAtomProp(string key,int atomid);

    int setProp(string key, string value);
    unsigned int getNumAtoms();
    int getNumConformers();
    RDKit::Conformer getConformer(int id);
    bool hasProp(string key);
    vector<string> getproplist();
    
    // atom & bond manipulations
    unsigned int addAtom (int atomid);
    // this is in development stage caution not working for the moment!!!!
    unsigned int addBond (unsigned int beginAtomIdx, unsigned int endAtomIdx,int bondtypeid);
    void setBondDir (int Bondid, int bonddirid);
    vector<int> getAtomNeighbors(int atomid);
    vector<double> getBondNeighbors(int atomid);
    vector<double> getAdjacencyMatrix(bool useBO);
    vector<int> getAtomicNums();
    vector<string> getSymbols();

    
    
    // static constructors
    static Molecule* newmolecule();
    static Molecule* MurckofromSmiles(string smi);
    static Molecule* fromSmiles(string smiles);
    static Molecule* Mol2BlockToMol(string molBlock);
    static Molecule* MolBlockToMol(string molBlock);
    static Molecule* fromSmarts(string smarts);
    static Molecule* molFromPickle(string pickle);
    
private:
    RWMol* rdmol;
    RWMol getMol() const {return *rdmol;}; // access to the RDkit mol object in private function not to share with javascript!

};




/* adding another class
 class Similarity
 {
 public:
 Similarity(RWMol *mol1, RWMol *mol2);
 
 ~Similarity();
 
 double Tanimoto();
 
 private:
 RWMol* rdmol1;
 RWMol* rdmol2;
 };
 
 
 
 Similarity* passThrough(Similarity* ptr) { return ptr; }
 */


Molecule* passThrough(Molecule* ptr) { return ptr; }

// Binding code
EMSCRIPTEN_BINDINGS(rdmol) {
    // register the vectors
    register_vector<string>("VectorString");
    register_vector<double>("VectorDouble");
    register_vector<float>("VectorFloat");
    register_vector<unsigned int>("VectorUint");
    register_vector<int>("Vectorint");
    register_map<boost::uint32_t,int>("MapIindexInt");
    register_map<int,string>("MapIntString");

    
    class_<Molecule>("Molecule")
    .function("Similarity",&Molecule::Similarity, allow_raw_pointers())
//    .function("getMol",&Molecule::getMol, allow_raw_pointers())

    .function("FindMolChiralCenters",&Molecule::FindMolChiralCenters, allow_raw_pointers())
    .function("addAtom",&Molecule::addAtom, allow_raw_pointers())
    .function("addBond",&Molecule::addBond, allow_raw_pointers())
    .function("setBondDir",&Molecule::setBondDir, allow_raw_pointers())
    .function("getNumAtoms", &Molecule::getNumAtoms, allow_raw_pointers())
    .function("getAtomNeighbors", &Molecule::getAtomNeighbors, allow_raw_pointers())
    .function("getBondNeighbors", &Molecule::getBondNeighbors, allow_raw_pointers())
    .function("getAdjacencyMatrix", &Molecule::getAdjacencyMatrix, allow_raw_pointers())
    .function("CanonicalRankAtoms", &Molecule::CanonicalRankAtoms, allow_raw_pointers())
    .function("picontacts", &Molecule::picontacts, allow_raw_pointers())
    .function("getAtomCountRingBonds", &Molecule::getAtomCountRingBonds, allow_raw_pointers())
    .function("getAtomValence", &Molecule::getAtomValence, allow_raw_pointers())
    .function("getAtomHeteroValence", &Molecule::getAtomHeteroValence, allow_raw_pointers())
    .function("getAtomHeavyValence", &Molecule::getAtomHeavyValence, allow_raw_pointers())

    // fingerprints
    .function("getAtomCode", &Molecule::getAtomCode, allow_raw_pointers())
    .function("getAtomPairFingerprint", &Molecule::getAtomPairFingerprint, allow_raw_pointers())
    .function("getHashedAtomPairFingerprint", &Molecule::getHashedAtomPairFingerprint, allow_raw_pointers())
    .function("getHashedAtomPairFingerprintAsBitVect", &Molecule::getHashedAtomPairFingerprintAsBitVect, allow_raw_pointers())
    .function("getRDKFP", &Molecule::getRDKFP, allow_raw_pointers())
    .function("getMorganFP", &Molecule::getMorganFP, allow_raw_pointers())
    .function("getMorganUFPkeys", &Molecule::getMorganUFPkeys, allow_raw_pointers())
    .function("getMorganFP_GetOnBits", &Molecule::getMorganFP_GetOnBits, allow_raw_pointers())
    .function("getMorganFP_getNonzeroElements", &Molecule::getMorganFP_getNonzeroElements, allow_raw_pointers())
    .function("getMorganFPlist", &Molecule::getMorganFPlist, allow_raw_pointers())

    .function("getLayeredFP", &Molecule::getLayeredFP, allow_raw_pointers())
    .function("getMACCSFP", &Molecule::getMACCSFP, allow_raw_pointers())
    .function("getPatternFP", &Molecule::getPatternFP, allow_raw_pointers())
    
    // molops basic functions
    .function("addHs", &Molecule::addHs, allow_raw_pointers())
    .function("removeHs", &Molecule::removeHs, allow_raw_pointers())
    .function("sanitizeMol", &Molecule::sanitizeMol, allow_raw_pointers())
    .function("findSSSR", &Molecule::findSSSR, allow_raw_pointers())
    .function("findSSSRnumber", &Molecule::findSSSRnumber, allow_raw_pointers())
    
    .function("cleanUp", &Molecule::cleanUp, allow_raw_pointers())
    .function("Kekulize", &Molecule::Kekulize, allow_raw_pointers())
    
    // 2D & 3D molecules
    .function("compute2DCoords", &Molecule::compute2DCoords, allow_raw_pointers())
    .function("EmbedMolecule", select_overload<int()>(&Molecule::EmbedMolecule), allow_raw_pointers())
    .function("EmbedMoleculearg", select_overload<int(unsigned int,int)>(&Molecule::EmbedMolecule), allow_raw_pointers())
    .function("EmbedMultipleConfs", select_overload<vector<int>()>(&Molecule::EmbedMultipleConfs), allow_raw_pointers())
    .function("EmbedMultipleConfsarg", select_overload<vector<int>(unsigned int,unsigned int,int)>(&Molecule::EmbedMultipleConfs), allow_raw_pointers())
    .function("MMFFoptimizeMolecule", select_overload<vector<double>()>(&Molecule::MMFFoptimizeMolecule), allow_raw_pointers())
    .function("MMFFoptimizeMoleculearg", select_overload<vector<double>(int,string)>(&Molecule::MMFFoptimizeMolecule), allow_raw_pointers())
    .function("MMFFOptimizeMoleculeConfs", &Molecule::MMFFOptimizeMoleculeConfs, allow_raw_pointers())
    .function("UFFOptimizeMolecule", &Molecule::UFFOptimizeMolecule, allow_raw_pointers())
    
    // drawing molecules
    .function("Drawing2D", &Molecule::Drawing2D, allow_raw_pointers())
    .function("getAtomsPos2D", &Molecule::getAtomsPos2D, allow_raw_pointers())

    

    // Data compression
    .function("MolToBinary", &Molecule::MolToBinary, allow_raw_pointers())
    
    
    .function("getPath", &Molecule::getPath, allow_raw_pointers())
    
    // writer basic functions
    .function("toMolfile", &Molecule::toMolfile, allow_raw_pointers())
    .function("toSmiles", &Molecule::toSmiles, allow_raw_pointers())
    
    
    // testing functions ... not working correctly
    //.function("save", &Molecule::save, allow_raw_pointers())
    //.function("load", &Molecule::load, allow_raw_pointers())
    //.function("nodereadwrite", &Molecule::nodereadwrite, allow_raw_pointers())
    //.function("nodereadwritewithdata", &Molecule::nodereadwritewithdata, allow_raw_pointers())
    
    //.function("sdwritefile", &Molecule::sdwritefile, allow_raw_pointers())
    //.function("sdreadfile", &Molecule::sdreadfile, allow_raw_pointers())
    
    .function("sdwriteConfs", &Molecule::sdwriteConfs, allow_raw_pointers())
    //.function("writefile", &Molecule::writefile, allow_raw_pointers())
    //.function("readfile", &Molecule::readfile, allow_raw_pointers())
    
    // properties
    .function("getproplist", &Molecule::getproplist, allow_raw_pointers())
    .function("getProp", &Molecule::getProp, allow_raw_pointers())
    .function("getAtomProp", &Molecule::getAtomProp, allow_raw_pointers())

    .function("getNumConformers", &Molecule::getNumConformers, allow_raw_pointers())
    .function("getConformer", &Molecule::getConformer, allow_raw_pointers())
    .function("setProp", &Molecule::setProp, allow_raw_pointers())
    .function("hasProp", &Molecule::hasProp, allow_raw_pointers())
    
    // susbtructure
    .function("GetSubstructMatches", &Molecule::GetSubstructMatches, allow_raw_pointers())
    .function("HasSubstructMatchStr", &Molecule::HasSubstructMatchStr, allow_raw_pointers())
    .function("GetSubstructMatchesNumber", &Molecule::GetSubstructMatchesNumber, allow_raw_pointers())
    
    
    // similarity
    .function("TanimotoSimilarityfromSmile", &Molecule::TanimotoSimilarityfromSmile, allow_raw_pointers())
    .function("DiceSimilarityfromSmile", &Molecule::DiceSimilarityfromSmile, allow_raw_pointers())
    .function("TverskySimilarityfromSmile", &Molecule::TverskySimilarityfromSmile, allow_raw_pointers())

    .function("AlignMol", &Molecule::AlignMol, allow_raw_pointers())
    .function("AlignMolConformers", &Molecule::AlignMolConformers, allow_raw_pointers())
    //.function("AlignMolConformersRMSlist", &Molecule::AlignMolConformersRMSlist, allow_raw_pointers())
    .function("getConformersRMS", &Molecule::getConformersRMS, allow_raw_pointers())


    .function("getNumMacrocycles",&Molecule::getNumMacrocycles, allow_raw_pointers())
    .function("getNumSpiroAtoms",&Molecule::getNumSpiroAtoms, allow_raw_pointers())
    .function("getNumBridgeheadAtoms",&Molecule::getNumBridgeheadAtoms, allow_raw_pointers())
    // descriptors used in calc_all_desc
    .function("getMW", &Molecule::getMW, allow_raw_pointers())
    .function("ExactMW",&Molecule::ExactMW ,allow_raw_pointers())
    .function("Formula",&Molecule::Formula ,allow_raw_pointers())
    .function("Chi0v",&Molecule::Chi0v ,allow_raw_pointers())
    .function("Chi1v",&Molecule::Chi1v ,allow_raw_pointers())
    .function("Chi2v",&Molecule::Chi2v ,allow_raw_pointers())
    .function("Chi3v",&Molecule::Chi3v ,allow_raw_pointers())
    .function("Chi4v",&Molecule::Chi4v ,allow_raw_pointers())
    .function("ChiNv",&Molecule::ChiNv ,allow_raw_pointers())

    .function("Chi0n",&Molecule::Chi0n ,allow_raw_pointers())
    .function("Chi1n",&Molecule::Chi1n ,allow_raw_pointers())
    .function("Chi2n",&Molecule::Chi2n ,allow_raw_pointers())
    .function("Chi3n",&Molecule::Chi3n ,allow_raw_pointers())
    .function("Chi4n",&Molecule::Chi4n ,allow_raw_pointers())
    .function("ChiNn",&Molecule::ChiNn ,allow_raw_pointers())

    .function("HallKierAlpha",&Molecule::HallKierAlpha ,allow_raw_pointers())
    .function("Kappa1",&Molecule::Kappa1 ,allow_raw_pointers())
    .function("Kappa2",&Molecule::Kappa2 ,allow_raw_pointers())
    .function("Kappa3",&Molecule::Kappa3 ,allow_raw_pointers())
    .function("logp_mr",&Molecule::logp_mr ,allow_raw_pointers())
    .function("getCrippenAtomContribs",&Molecule::getCrippenAtomContribs ,allow_raw_pointers())
    .function("LipinskiHBA",&Molecule::LipinskiHBA ,allow_raw_pointers())
    .function("LipinskiHBD",&Molecule::LipinskiHBD ,allow_raw_pointers())
    .function("NumRotatableBonds",&Molecule::NumRotatableBonds ,allow_raw_pointers())
    .function("NumHBD",&Molecule::NumHBD ,allow_raw_pointers())
    .function("NumHBA",&Molecule::NumHBA ,allow_raw_pointers())
    .function("NumHeteroatoms",&Molecule::NumHeteroatoms ,allow_raw_pointers())
    .function("NumAmideBonds",&Molecule::NumAmideBonds ,allow_raw_pointers())
    .function("FractionCSP3",&Molecule::FractionCSP3 ,allow_raw_pointers())
    .function("NumRings",&Molecule::NumRings ,allow_raw_pointers())
    .function("NumAromaticRings",&Molecule::NumAromaticRings ,allow_raw_pointers())
    .function("NumAliphaticRings",&Molecule::NumAliphaticRings ,allow_raw_pointers())
    .function("NumSaturatedRings",&Molecule::NumSaturatedRings ,allow_raw_pointers())
    .function("NumHeterocycles",&Molecule::NumHeterocycles ,allow_raw_pointers())
    .function("NumAromaticHeterocycles",&Molecule::NumAromaticHeterocycles ,allow_raw_pointers())
    .function("NumAromaticCarbocycles",&Molecule::NumAromaticCarbocycles ,allow_raw_pointers())
    .function("NumSaturatedHeterocycles",&Molecule::NumSaturatedHeterocycles ,allow_raw_pointers())
    .function("NumSaturatedCarbocycles",&Molecule::NumSaturatedCarbocycles ,allow_raw_pointers())
    .function("NumAliphaticHeterocycles",&Molecule::NumAliphaticHeterocycles ,allow_raw_pointers())
    .function("NumAliphaticCarbocycles",&Molecule::NumAliphaticCarbocycles ,allow_raw_pointers())
    .function("LabuteASA",&Molecule::LabuteASA ,allow_raw_pointers())
    .function("getASAContribs",&Molecule::getASAContribs ,allow_raw_pointers())

    .function("TPSA",&Molecule::TPSA ,allow_raw_pointers())
    .function("getTPSAAtomContribs",&Molecule::getTPSAAtomContribs ,allow_raw_pointers())

    .function("SlogP_VSA",&Molecule::SlogP_VSA ,allow_raw_pointers())
    .function("SMR_VSA",&Molecule::SMR_VSA ,allow_raw_pointers())
    .function("PEO_VSA",&Molecule::PEO_VSA ,allow_raw_pointers())
    .function("MQNs",&Molecule::MQNs ,allow_raw_pointers())
    .function("computeGasteigerCharges",&Molecule::computeGasteigerCharges ,allow_raw_pointers())
    .function("getAtomicNums",&Molecule::getAtomicNums ,allow_raw_pointers())
    .function("getSymbols",&Molecule::getSymbols ,allow_raw_pointers())


    // create class from smiles or smarts
    // .function("Mol2FileToMol", &Molecule::Mol2FileToMol, allow_raw_pointers())
    .class_function("newmolecule", &Molecule::newmolecule, allow_raw_pointers())
    .class_function("MurckofromSmiles", &Molecule::MurckofromSmiles, allow_raw_pointers())
    .class_function("MolBlockToMol", &Molecule::MolBlockToMol, allow_raw_pointers())
    .class_function("Mol2BlockToMol", &Molecule::Mol2BlockToMol, allow_raw_pointers())
    .class_function("fromSmiles", &Molecule::fromSmiles, allow_raw_pointers())
    .class_function("fromSmarts", &Molecule::fromSmarts, allow_raw_pointers())
    .class_function("molFromPickle", &Molecule::molFromPickle, allow_raw_pointers());
    
    /* adding another class ...
     class_<Similarity>("Similarity")
     .function("Tanimoto",&Similarity::Tanimoto, allow_raw_pointers());
     */
}

