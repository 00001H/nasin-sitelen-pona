#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvariadic-macros"
#include<fcitx/inputmethodengine.h>
#include<fcitx-config/iniparser.h>
#include<fcitx/addonfactory.h>
#include<fcitx/addonmanager.h>
#include<fcitx/inputcontext.h>
#include<fcitx/inputpanel.h>
#include<fcitx/instance.h>
#pragma GCC diagnostic pop
#include<unordered_map>
#include<filesystem>
#include<fstream>
#include<cstdlib>
#include<cassert>
#include<utility>
#include<vector>
#include<string>
using namespace std::literals;
static fcitx::Text u2t(std::u8string_view sv){
    return fcitx::Text(std::string(reinterpret_cast<const char*>(sv.data()),sv.size()));
}
struct NspState : fcitx::InputContextProperty{
    std::u8string sequence;
};
const inline std::unordered_map<std::u8string,std::u8string_view> NIMI_MAP{
    {u8"a"s,u8"\U000F1900"sv},
    {u8"e"s,u8"\U000F1909"sv},
    {u8"o"s,u8"\U000F1944"sv},
    {u8"n"s,u8"\U000F1986"sv},
    {u8"en"s,u8"\U000F190A"sv},
    {u8"jo"s,u8"\U000F1913"sv},
    {u8"ko"s,u8"\U000F191C"sv},
    {u8"la"s,u8"\U000F1921"sv},
    {u8"li"s,u8"\U000F1927"sv},
    {u8"ma"s,u8"\U000F1930"sv},
    {u8"mi"s,u8"\U000F1934"sv},
    {u8"mu"s,u8"\U000F1939"sv},
    {u8"ni"s,u8"\U000F1941"sv},
    {u8"pi"s,u8"\U000F194D"sv},
    {u8"pu"s,u8"\U000F1955"sv},
    {u8"tu"s,u8"\U000F196E"sv},
    {u8"ku"s,u8"\U000F1988"sv},
    {u8"ala"s,u8"\U000F1902"sv},
    {u8"ale"s,u8"\U000F1904"sv},
    {u8"anu"s,u8"\U000F1907"sv},
    {u8"ijo"s,u8"\U000F190C"sv},
    {u8"ike"s,u8"\U000F190D"sv},
    {u8"ilo"s,u8"\U000F190E"sv},
    {u8"jan"s,u8"\U000F1911"sv},
    {u8"ken"s,u8"\U000F1918"sv},
    {u8"kon"s,u8"\U000F191D"sv},
    {u8"len"s,u8"\U000F1925"sv},
    {u8"lon"s,u8"\U000F192C"sv},
    {u8"mun"s,u8"\U000F193A"sv},
    {u8"ona"s,u8"\U000F1946"sv},
    {u8"pan"s,u8"\U000F194B"sv},
    {u8"sin"s,u8"\U000F195D"sv},
    {u8"tan"s,u8"\U000F1967"sv},
    {u8"uta"s,u8"\U000F1970"sv},
    {u8"wan"s,u8"\U000F1973"sv},
    {u8"kin"s,u8"\U000F1979"sv},
    {u8"oko"s,u8"\U000F197A"sv},
    {u8"anpa"s,u8"\U000F1905"sv},
    {u8"ante"s,u8"\U000F1906"sv},
    {u8"awen"s,u8"\U000F1908"sv},
    {u8"esun"s,u8"\U000F190B"sv},
    {u8"insa"s,u8"\U000F190F"sv},
    {u8"jaki"s,u8"\U000F1910"sv},
    {u8"jelo"s,u8"\U000F1912"sv},
    {u8"kala"s,u8"\U000F1914"sv},
    {u8"kama"s,u8"\U000F1916"sv},
    {u8"kasi"s,u8"\U000F1917"sv},
    {u8"kili"s,u8"\U000F191A"sv},
    {u8"kule"s,u8"\U000F191E"sv},
    {u8"kute"s,u8"\U000F1920"sv},
    {u8"lape"s,u8"\U000F1922"sv},
    {u8"laso"s,u8"\U000F1923"sv},
    {u8"lawa"s,u8"\U000F1924"sv},
    {u8"lete"s,u8"\U000F1926"sv},
    {u8"lili"s,u8"\U000F1928"sv},
    {u8"lipu"s,u8"\U000F192A"sv},
    {u8"loje"s,u8"\U000F192B"sv},
    {u8"luka"s,u8"\U000F192D"sv},
    {u8"lupa"s,u8"\U000F192F"sv},
    {u8"mama"s,u8"\U000F1931"sv},
    {u8"mani"s,u8"\U000F1932"sv},
    {u8"meli"s,u8"\U000F1933"sv},
    {u8"mije"s,u8"\U000F1935"sv},
    {u8"moku"s,u8"\U000F1936"sv},
    {u8"moli"s,u8"\U000F1937"sv},
    {u8"musi"s,u8"\U000F193B"sv},
    {u8"mute"s,u8"\U000F193C"sv},
    {u8"nasa"s,u8"\U000F193E"sv},
    {u8"nena"s,u8"\U000F1940"sv},
    {u8"nimi"s,u8"\U000F1942"sv},
    {u8"noka"s,u8"\U000F1943"sv},
    {u8"olin"s,u8"\U000F1945"sv},
    {u8"open"s,u8"\U000F1947"sv},
    {u8"pali"s,u8"\U000F1949"sv},
    {u8"pana"s,u8"\U000F194C"sv},
    {u8"pini"s,u8"\U000F1950"sv},
    {u8"pipi"s,u8"\U000F1951"sv},
    {u8"poka"s,u8"\U000F1952"sv},
    {u8"poki"s,u8"\U000F1953"sv},
    {u8"pona"s,u8"\U000F1954"sv},
    {u8"sama"s,u8"\U000F1956"sv},
    {u8"seli"s,u8"\U000F1957"sv},
    {u8"selo"s,u8"\U000F1958"sv},
    {u8"seme"s,u8"\U000F1959"sv},
    {u8"sewi"s,u8"\U000F195A"sv},
    {u8"sike"s,u8"\U000F195C"sv},
    {u8"sina"s,u8"\U000F195E"sv},
    {u8"sona"s,u8"\U000F1961"sv},
    {u8"suli"s,u8"\U000F1963"sv},
    {u8"suno"s,u8"\U000F1964"sv},
    {u8"supa"s,u8"\U000F1965"sv},
    {u8"suwi"s,u8"\U000F1966"sv},
    {u8"taso"s,u8"\U000F1968"sv},
    {u8"tawa"s,u8"\U000F1969"sv},
    {u8"telo"s,u8"\U000F196A"sv},
    {u8"toki"s,u8"\U000F196C"sv},
    {u8"tomo"s,u8"\U000F196D"sv},
    {u8"unpa"s,u8"\U000F196F"sv},
    {u8"walo"s,u8"\U000F1972"sv},
    {u8"waso"s,u8"\U000F1974"sv},
    {u8"wawa"s,u8"\U000F1975"sv},
    {u8"weka"s,u8"\U000F1976"sv},
    {u8"wile"s,u8"\U000F1977"sv},
    {u8"leko"s,u8"\U000F197C"sv},
    {u8"soko"s,u8"\U000F1981"sv},
    {u8"meso"s,u8"\U000F1982"sv},
    {u8"pake"s,u8"\U000F19A0"sv},
    {u8"powe"s,u8"\U000F19A3"sv},
    {u8"akesi"s,u8"\U000F1901"sv},
    {u8"alasa"s,u8"\U000F1903"sv},
    {u8"kiwen"s,u8"\U000F191B"sv},
    {u8"linja"s,u8"\U000F1929"sv},
    {u8"lukin"s,u8"\U000F192E"sv},
    {u8"monsi"s,u8"\U000F1938"sv},
    {u8"nanpa"s,u8"\U000F193D"sv},
    {u8"nasin"s,u8"\U000F193F"sv},
    {u8"pilin"s,u8"\U000F194E"sv},
    {u8"tenpo"s,u8"\U000F196B"sv},
    {u8"utala"s,u8"\U000F1971"sv},
    {u8"tonsi"s,u8"\U000F197E"sv},
    {u8"epiku"s,u8"\U000F1983"sv},
    {u8"apeja"s,u8"\U000F19A1"sv},
    {u8"kalama"s,u8"\U000F1915"sv},
    {u8"kulupu"s,u8"\U000F191F"sv},
    {u8"pakala"s,u8"\U000F1948"sv},
    {u8"palisa"s,u8"\U000F194A"sv},
    {u8"pimeja"s,u8"\U000F194F"sv},
    {u8"sijelo"s,u8"\U000F195B"sv},
    {u8"sinpin"s,u8"\U000F195F"sv},
    {u8"soweli"s,u8"\U000F1962"sv},
    {u8"namako"s,u8"\U000F1978"sv},
    {u8"kipisi"s,u8"\U000F197B"sv},
    {u8"jasima"s,u8"\U000F197F"sv},
    {u8"lanpan"s,u8"\U000F1985"sv},
    {u8"majuna"s,u8"\U000F19A2"sv},
    {u8"kepeken"s,u8"\U000F1919"sv},
    {u8"sitelen"s,u8"\U000F1960"sv},
    {u8"monsuta"s,u8"\U000F197D"sv},
    {u8"kokosila"s,u8"\U000F1984"sv},
    {u8"misikeke"s,u8"\U000F1987"sv},
    {u8"kijetesantakalu"s,u8"\U000F1980"sv},
};
using ndb_t = std::vector<std::pair<std::u8string,std::u8string_view>>;
static ndb_t rdnimi(){
    ndb_t nimi;
    if(char* home=std::getenv("HOME")){
        std::ifstream dbf{std::filesystem::path(home)/"nsp-map",std::ios_base::in};
        std::string line;
        std::u8string token;
        std::u8string_view ucsur;
        while(!dbf.eof()){
            if(!dbf.good()){
                throw std::runtime_error("nsp-map read failed");
            }
            getline(dbf,line); // ADL
            if(dbf.eof() && line.empty()){
                break;
            }
            token.clear();
            ucsur = {};
            for(char c : line){
                if(c==' '){
                    if(!ucsur.data()){
                        ucsur = NIMI_MAP.at(token);
                    }else{
                        nimi.emplace_back(std::move(token),ucsur);
                    }
                    token.clear();
                }else{
                    token.push_back(static_cast<char8_t>(c));
                }
            }
            if(!token.empty()){
                nimi.emplace_back(std::move(token),ucsur);
            }
        }
    }else{
        throw std::runtime_error("No user home directory");
    }
    return nimi;
}
constexpr static bool vowel(char8_t c){
    switch(c){
        case u8'a': case u8'e': case u8'i': case u8'o': case u8'u':
            return true;
        default:
            return false;
    }
}
constexpr static char8_t fz_voicedness(char8_t c){
    switch(c){
        case u8'b':
            return u8'p';
        case u8'd':
            return u8't';
        case u8'g':
            return u8'k';
        case u8'z':
            return u8's';
        default:
            return c;
    }
}
#define Z_FCITX_MKKEY(x) fcitx::Key(FcitxKey_ ## x)
FCITX_CONFIGURATION(NspConfig,
    fcitx::KeyListOption cancelkey{this,"kcancel"s,"Compose cancel hotkey"s,{Z_FCITX_MKKEY(Escape)},fcitx::KeyListConstrain(fcitx::KeyConstrainFlag::AllowModifierLess)};
)
class NspBackend : public fcitx::InputMethodEngineV2{
    fcitx::FactoryFor<NspState> state_f;
    NspConfig conf;
    ndb_t nimidb;
    std::unordered_set<char8_t> used_chars;
    NspState& state_from_context(fcitx::InputContext& c){
        return *c.propertyFor(&state_f);
    }
    enum KeyResult{
        IGNORED,
        SUPPRESSED,
        HANDLED
    };
    KeyResult handle(fcitx::KeyEvent& ke){
        if(ke.isRelease()) return IGNORED;
        fcitx::InputContext* ctx{ke.inputContext()};
        NspState& state{state_from_context(*ctx)};
        if(!ctx->inputPanel().preedit().empty()){
            if(ke.key().checkKeyList(*conf.cancelkey)){
                state.sequence.clear();
                ctx->inputPanel().reset();
                return HANDLED;
            }
        }
        const std::string keyv{ke.key().toString(fcitx::KeyStringFormat::Localized)};
        if(ke.key().check(FcitxKey_BackSpace)){
            if(state.sequence.empty()){
                return IGNORED;
            }
            state.sequence.pop_back();
            if(state.sequence.empty()){
                ctx->inputPanel().reset();
                return HANDLED;
            }
            ctx->inputPanel().setPreedit(u2t(state.sequence));
        }else if(ke.key().check(FcitxKey_asciicircum)){
            ctx->commitString("\U000F1996"s);
        }else if(ke.key().check(FcitxKey_grave)){
            ctx->commitString("\U000F199C"s);
        }else if(ke.key().check(FcitxKey_colon)){
            ctx->commitString("\U000F199D"s);
        }else if(keyv.size()==1){
            char8_t letter = static_cast<char8_t>(keyv.front());
            if(used_chars.contains(letter)){
                state.sequence.push_back(letter);
                ctx->inputPanel().setPreedit(u2t(state.sequence));
            }else{
                return IGNORED;
            }
        }else{
            return IGNORED;
        }
        for(const auto& [k,v] : nimidb){
            if(state.sequence == k){
                ctx->commitString(std::string(reinterpret_cast<const char*>(v.data()),v.size()));
                state.sequence.clear();
                ctx->inputPanel().reset();
            }
        }
        return HANDLED;
    }
    public:
        NspBackend(fcitx::Instance* inst) : state_f([](fcitx::InputContext&){return new NspState();}){
            inst->inputContextManager().registerProperty("toki-state"s,&state_f);
            reloadConfig();
        }
        void keyEvent(const fcitx::InputMethodEntry&,fcitx::KeyEvent& ke) override{
            switch(handle(ke)){
                case HANDLED:
                    ke.inputContext()->updateUserInterface(fcitx::UserInterfaceComponent::InputPanel);
                    ke.inputContext()->updatePreedit();
                    [[fallthrough]];
                case SUPPRESSED:
                    ke.filterAndAccept();
                    break;
                case IGNORED:;
            }
        }
        static constexpr char configFile[] = "conf/toki-sitelen.conf";
        void reloadConfig() override{
            readAsIni(conf,configFile);
            nimidb = rdnimi();
            used_chars.clear();
            for(const auto& [k,_] : nimidb){
                for(char8_t c : k){
                    used_chars.emplace(c);
                }
            }
        }
        const fcitx::Configuration* getConfig() const override{
            return &conf;
        }
        void setConfig(const fcitx::RawConfig& config) override{
            conf.load(config,true);
            safeSaveAsIni(conf,configFile);
        }
};
class NspBackendFactory : public fcitx::AddonFactory{
    fcitx::AddonInstance* create(fcitx::AddonManager* mgr) override{
        return new NspBackend(mgr->instance());
    }
};
FCITX_ADDON_FACTORY(NspBackendFactory)
