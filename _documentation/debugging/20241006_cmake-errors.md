ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: ios_base::failbit set: iostream stream error
ERROR::PROGRAM_LINKING_ERROR of type: PROGRAM
Vertex shader(s) failed to link, fragment shader(s) failed to link.
Vertex link error: INVALID_OPERATION.
ERROR: error(#97) No program main found
fragment link error: INVALID_OPERATION.
ERROR: error(#97) No program main found


"data\/(.*)"
DATA_DIR + std::string("$1")

"source/shaders\/(.*)"
SHADER_DIR + std::string("$1")



application.obj : error LNK2001: unresolved external symbol 
"public: static class std::vector<struct ShaderPaths,class std::allocator<struct ShaderPaths> > const RelativePaths::shader_paths" 
(?shader_paths@RelativePaths@@2V?$vector@UShaderPaths@@V?$allocator@UShaderPaths@@@std@@@std@@B) 
[C:\Users\kutay\OneDrive\Documents\GitHub\study_opengl\build\project_test.vcxproj]


application.obj : 
error LNK2019: unresolved external symbol "public: __cdecl TestScene::TestScene(void)" 
(??0TestScene@@QEAA@XZ) 
referenced in function "private: void __cdecl Application::loadSceneData(class std::unordered_map<class std::basic_string<char,struct std::char_traits<char>,clas
s std::allocator<char> >,class std::unordered_map<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,struct std::hash<class std::basic_string<char,struct std::char_t 
raits<char>,class std::allocator<char> > >,struct std::equal_to<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >,class std::allocator<struct std::pair<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const ,cla 
ss std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > >,struct std::hash<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >,struct std::equal_to<class std::basic_string<char,struct std::char_traits<char>,class std::a 
llocator<char> > >,class std::allocator<struct std::pair<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const ,class std::unordered_map<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::basic_string<c 
har,struct std::char_traits<char>,class std::allocator<char> >,struct std::hash<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >,struct std::equal_to<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >,class std 
::allocator<struct std::pair<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const ,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > > > > > const &)" 
(?loadSceneData@Application@@AEAAXAEBV?$unordered_map@V? 
$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$unordered_map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@U?$hash@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@U?$equal_to@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ 
@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@std@@@2@@2@U?$hash@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@U?$equal_to@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_ 
string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$unordered_map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@U?$hash@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@U?$equal_to@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$a 
llocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@std@@@2@@2@@std@@@2@@std@@@Z) 
[C:\Users\kutay\OneDrive\Documents\GitHub\study_opengl\build\project_test.vcxproj]


application.obj : 

error LNK2019: unresolved external symbol 
"bool __cdecl ImGui_ImplGlfw_InitForOpenGL(struct GLFWwindow *,bool)" 

(?ImGui_ImplGlfw_InitForOpenGL@@YA_NPEAUGLFWwindow@@_N@Z) 

referenced in function "

private: void __cdecl Application::initUISystem(char const * &)" (?initUISyste
m@Application@@AEAAXAEAPEBD@Z) 

[C:\Users\kutay\OneDrive\Documents\GitHub\study_opengl\build\project_test.vcxproj]


application.obj : 

application.obj : error LNK2019: unresolved external symbol <gladLoadGLLoader> referenced in function "public: bool __cdecl 

Application::initialize(class std::unordered_map<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::unordered_map<class 
std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,struct std::hash<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >,struct std::e 
qual_to<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >,class std::allocator<struct std::pair<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const ,class std::basic_string<char,struct std::char_traits<char>, 
class std::allocator<char> > > > >,struct std::hash<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >,struct std::equal_to<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >,class std::allocator<struct std::pair 
<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const ,class std::unordered_map<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<c 
har> >,struct std::hash<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >,struct std::equal_to<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >,class std::allocator<struct std::pair<class std::basic_string<cha 
r,struct std::char_traits<char>,class std::allocator<char> > const ,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > > > > > const &)" 

(?initialize@Application@@QEAA_NAEBV?$unordered_map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std 
@@V?$unordered_map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@U?$hash@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@U?$equal_to@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_trait 
s@D@std@@V?$allocator@D@2@@std@@V12@@std@@@2@@2@U?$hash@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@U?$equal_to@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$un 
ordered_map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@U?$hash@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@U?$equal_to@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std 
@@V?$allocator@D@2@@std@@V12@@std@@@2@@2@@std@@@2@@std@@@Z) [C:\Users\kutay\OneDrive\Documents\GitHub\study_opengl\build\project_test.vcxproj]