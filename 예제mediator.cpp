// 지시자(mediator) interface
// (하나만 할꺼라면 없어도 된다)
class DialogDirector
{
public:
	virtual ~DialogDirector();

	virtual void ShowDialog();
	virtual void WidgetChanged(Widget*) = 0;
protected:
	DialogDirector();
	virtual void CreateWidgets() = 0;
};

// colleague interface 
// (하나만 할꺼라면 없어도 된다)
class MouseEvent;
class Widget
{
public:
	Widget(DialogDirector*);
	
	virtual void Changed();
	virtual void HandelMouse(MouseEvent& event);
private:
	DialogDirector* _director;
};

void Widget::Changed()	// colleague의 변경 사실을 mediator에게 알린다
{
	_director->WidgetChanged(this);
}

// colleague 구현 부분
class ListBox : public Widget
{
public:
	ListBox(DialogDirector*);

	virtual const char* GetSelection();
	virtual void HandleMouse(MouseEvent& event);
};

class EntryField : public Widget
{
public:
	EntryField(DialogDirector*);

	virtual void SetText(const char* text);
};

class Button : public Widget
{
public:
	Button(DialogDirector*);

	virtual void SetText(const char* text);
	virtual void HandleMouse(MouseEvent& event);
};

// 지시자(mediator) subClass
class FontDialogDirector : public DialogDirector
{
public:
	FontDialogDirector();
	virtual ~FontDialogDirector();

	virtual void WidgetChanged(Widget*);
protected:
	virtual void CreateWidgets();
private:
	Button* _Ok;
	Button* _cancel;
	ListBox* _fontList;
	EntryField* _fontName;
};

void FontDialogDirector::WidgetChanged(Widget *changed)
{
	if (changed == _fontList) {
		_fontName->SetText(_fontList->GetSelection());
	}
	else if (changed == _Ok) {
		//..
	}
	else if (changed == _cancel) {
		//....
	}
}

void FontDialogDirector::CreateWidgets()
{
	_Ok = new Button(this);
	_cancel = new Button(this);
	_fontList = new ListBox(this);
	_fontName = new EntryField(this);
}
