/* Copyright © 2000 Yiyun Liu <liuyiyun@terpmail.umd.edu>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. */


// Shader helpers
const auto program_success = [](const auto program) {
  auto params = -1;
  glGetProgramiv(program, GL_LINK_STATUS, &params);
  return GL_TRUE == params;
};

const auto program_info = [](const auto program) {
  std::ostringstream os;
  os << boost::format{"ERROR: could not link shader programme GL index %1%\n"} %
            program;
  os << [program]() {
    const std::size_t max_length = 2048;
    char log[max_length];
    glGetProgramInfoLog(program, max_length, nullptr, log);
    return std::string{log};
  }();
  return os.str();
};

const auto shader_success = [](const auto shader) {
  auto params = -1;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
  return params;
};

template <GLenum SHADER_TYPE>
auto load_shader(const std::string& shader_path) {
  auto ret = glCreateShader(SHADER_TYPE);
  std::ifstream fh{shader_path};
  std::stringstream buffer;
  buffer << fh.rdbuf();
  const auto str = buffer.str();
  const auto sp = str.c_str();
  glShaderSource(ret, 1, &sp, nullptr);
  glCompileShader(ret);
  return ret;
}

const auto shader_info = [](const auto shader) {

  std::ostringstream os;

  os << boost::format{"ERROR: GL shader index %1% did not compile\n"} % shader;

  os << [shader]() {
    const std::size_t max_length = 2048;
    char log[max_length];
    glGetShaderInfoLog(shader, max_length, nullptr, log);
    return std::string(log);
  }();
  return os.str();
};
