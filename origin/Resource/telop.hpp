
#pragma once
#include "../common.h"

//
// テロップ描画
//

class cTelop {
  Font font_;
  std::string text_;
  sstream num_;

public:
  cTelop() : font_(FONT_) {}

  // フォントサイズを指定
  void size(const int& size0) {
    font_.size(size0);
  }

  // 文字列を登録
  void textInput(const std::string& str) {
    text_ = str;
  }

  // 数字を含む文字列を登録
  void numberInput(const sstream& num0) {
    num_ << num0.str();
  }

  // 文字列をフラッシュする
  // TIPS: drawNumber() を使用したら必ず呼び出す
  void flushNumber() {
    num_.clear();
    num_.ignore(std::numeric_limits<std::streamsize>::max());
  }

  // 文字列の描画（登録済みの文字列を使用）
  void drawText(const Vec2f& pos, const Color& col) {
    font_.draw(text_, pos, col);
  }

  // 文字列の描画
  void drawText(const std::string& str, const Vec2f& pos, const Color& col) {
    font_.draw(str, pos, col);
  }

  // 数字を含む文字列の描画（登録済みの文字列を使用）
  void drawNumber(const Vec2f& pos, const Color& col) {
    font_.draw(num_.str(), pos, col);
  }

  // 数字を含む文字列の描画
  void drawNumber(const sstream& ostr, const Vec2f& pos, const Color& col) {
    font_.draw(ostr.str(), pos, col);
  }

  // 描画した時の文字列全体のサイズを取得
  // TIPS: 登録済みの文字列の長さを取得
  inline Vec2f getTextSize() {
    return font_.drawSize(text_);
  }

  // 描画した時の文字列全体のサイズを取得
  inline Vec2f getTextSize(const std::string& str) {
    return font_.drawSize(str);
  }

  // 描画した時の文字列の長さを取得
  // TIPS: 登録済みの文字列の長さを取得
  inline float getTextLength() {
    return font_.drawSize(text_).x();
  }

  // 描画した時の文字列の長さを取得
  inline float getTextLength(const std::string& str) {
    return font_.drawSize(str).x();
  }

  // 描画した時の数字を含む文字列全体のサイズを取得
  // TIPS: numberInput() で文字列を登録してから使う
  inline Vec2f getNumberSize() {
    return font_.drawSize(num_.str());
  }

  // 描画した時の数字を含む文字列の長さを取得
  // TIPS: numberInput() で文字列を登録してから使う
  inline float getNumberLength() {
    return font_.drawSize(num_.str()).x();
  }
};
