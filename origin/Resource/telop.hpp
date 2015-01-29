
#pragma once
#include "../common.h"

//
// �e���b�v�`��
//

class cTelop {
  Font font_;
  std::string text_;
  sstream num_;

public:
  cTelop() : font_(FONT_) {}

  // �t�H���g�T�C�Y���w��
  void size(const int& size0) {
    font_.size(size0);
  }

  // �������o�^
  void textInput(const std::string& str) {
    text_ = str;
  }

  // �������܂ޕ������o�^
  void numberInput(const sstream& num0) {
    num_ << num0.str();
  }

  // ��������t���b�V������
  // TIPS: drawNumber() ���g�p������K���Ăяo��
  void flushNumber() {
    num_.clear();
    num_.ignore(std::numeric_limits<std::streamsize>::max());
  }

  // ������̕`��i�o�^�ς݂̕�������g�p�j
  void drawText(const Vec2f& pos, const Color& col) {
    font_.draw(text_, pos, col);
  }

  // ������̕`��
  void drawText(const std::string& str, const Vec2f& pos, const Color& col) {
    font_.draw(str, pos, col);
  }

  // �������܂ޕ�����̕`��i�o�^�ς݂̕�������g�p�j
  void drawNumber(const Vec2f& pos, const Color& col) {
    font_.draw(num_.str(), pos, col);
  }

  // �������܂ޕ�����̕`��
  void drawNumber(const sstream& ostr, const Vec2f& pos, const Color& col) {
    font_.draw(ostr.str(), pos, col);
  }

  // �`�悵�����̕�����S�̂̃T�C�Y���擾
  // TIPS: �o�^�ς݂̕�����̒������擾
  inline Vec2f getTextSize() {
    return font_.drawSize(text_);
  }

  // �`�悵�����̕�����S�̂̃T�C�Y���擾
  inline Vec2f getTextSize(const std::string& str) {
    return font_.drawSize(str);
  }

  // �`�悵�����̕�����̒������擾
  // TIPS: �o�^�ς݂̕�����̒������擾
  inline float getTextLength() {
    return font_.drawSize(text_).x();
  }

  // �`�悵�����̕�����̒������擾
  inline float getTextLength(const std::string& str) {
    return font_.drawSize(str).x();
  }

  // �`�悵�����̐������܂ޕ�����S�̂̃T�C�Y���擾
  // TIPS: numberInput() �ŕ������o�^���Ă���g��
  inline Vec2f getNumberSize() {
    return font_.drawSize(num_.str());
  }

  // �`�悵�����̐������܂ޕ�����̒������擾
  // TIPS: numberInput() �ŕ������o�^���Ă���g��
  inline float getNumberLength() {
    return font_.drawSize(num_.str()).x();
  }
};
