#include <wx/wx.h>
#include <wx/toolbar.h>
#include <wx/artprov.h>
#include <wx/filedlg.h>  // For wxFileDialog
#include <wx/msgdlg.h>   // For wxMessageBox
#include <wx/dcclient.h>
#include <cmath>
#include <vector>

// MyApp class
enum
{
    Show_Shaped = 100,//���ڰ���ʾͼƬ�¼�
    Show_Draw = 101//�󶨻�ͼ����
};

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

#pragma region Frame

// MyFrame class
#pragma region MyFrame

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

private:
    void OnImportCAD(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnExportPDF(wxCommandEvent& event);
    void OnClearCanvas(wxCommandEvent& event);
    void OnDrawNOT(wxCommandEvent& event);
    void OnDrawOR(wxCommandEvent& event);
    void OnDrawAND(wxCommandEvent& event);
    void Onlianxian(wxCommandEvent& event);
    void OnUndo(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    void SaveCanvasAsPNG(const wxString& filename);
    void OnDraw0(wxCommandEvent& event);
    void OnDraw1(wxCommandEvent& event);

    void OnPaint(wxPaintEvent& event);
    void OnMouseDown(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnMouseUp(wxMouseEvent& event);
    void DrawShapes(wxMemoryDC& dc);
    void DrawGrid(wxMemoryDC& dc); // ��������������
    void UpdateCanvas();

    wxDECLARE_EVENT_TABLE();

    wxBitmap m_canvas;
    wxPoint m_startPoint;
    wxPoint m_endPoint;
    bool m_drawing;
    bool m_drawOR;
    bool m_drawAND;
    bool m_drawNOT;
    bool m_lianxian;
    bool m_draw0;
    bool m_draw1;

    struct Shape {
        wxPoint start;
        wxPoint end;
        bool isOR;
        bool isNOT;
        bool islianxian;
        bool is0;
        bool is1;
    };

    std::vector<Shape> m_shapes;

    const int GRID_SIZE = 20; // ������
};

#pragma endregion

#pragma region ShapedFrame
class ShapedFrame :public wxFrame
{
public:
    ShapedFrame(wxFrame* parent);
    void OnMouseMove(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnPaint(wxPaintEvent& event);
    void SetWindowShape();
    void OnExit(wxMouseEvent& event);

    wxBitmap m_bitmap;
    wxPoint m_delta;
    bool isClicked;

private:
    DECLARE_EVENT_TABLE();

    enum Shape_Kind
    {
        Shape_None,
        Shape_Star
    }m_shapeKind;
};
#pragma endregion

#pragma region DrawFrame
//class DrawFrame : public wxFrame {
//public:
//    DrawFrame(const wxString& title);
//
//private:
//    void OnImportCAD(wxCommandEvent& event);
//    void OnSave(wxCommandEvent& event);
//    void OnExportPDF(wxCommandEvent& event);
//    void OnClearCanvas(wxCommandEvent& event);
//    void OnDrawRectangle(wxCommandEvent& event);
//    void OnDrawCircle(wxCommandEvent& event);
//    void OnDrawLine(wxCommandEvent& event);
//    void OnUndo(wxCommandEvent& event);
//    void OnAbout(wxCommandEvent& event);
//    void OnQuit(wxCommandEvent& event);
//
//    void OnPaint(wxPaintEvent& event);
//    void OnMouseDown(wxMouseEvent& event);
//    void OnMouseMove(wxMouseEvent& event);
//    void OnMouseUp(wxMouseEvent& event);
//    void DrawShapes(wxMemoryDC& dc);
//
//    wxDECLARE_EVENT_TABLE();
//
//    wxBitmap m_canvas;
//    wxPoint m_startPoint;
//    wxPoint m_endPoint;
//    bool m_drawing;
//    bool m_drawCircle;
//    bool m_drawLine;
//    bool m_drawRectangle;
//
//    struct Shape {
//        wxPoint start;
//        wxPoint end;
//        bool isCircle;
//        bool isRectangle;
//    };
//
//    std::vector<Shape> m_shapes;
//};

#pragma endregion

#pragma region SizerPanel
class SizerPanel :public wxPanel
{
public:
    SizerPanel(wxBoxSizer* sizer, wxPanel* panel, wxFrame* parent);
    void ButtonAnd(wxCommandEvent& event, wxFrame* frame);
    void ButtonOr(wxCommandEvent& event, wxFrame* frame);
    void ButtonNot(wxCommandEvent& event, wxFrame* frame);
private:
    DECLARE_EVENT_TABLE();

};
#pragma endregion


#pragma endregion


#pragma region EventTable

#pragma region MyFrameEvent

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(1001, MyFrame::OnImportCAD)
EVT_MENU(1002, MyFrame::OnSave)
EVT_MENU(1003, MyFrame::OnExportPDF)
EVT_MENU(1004, MyFrame::OnClearCanvas)
EVT_MENU(1005, MyFrame::OnDrawNOT)
EVT_MENU(1006, MyFrame::OnDrawOR)
EVT_MENU(1007, MyFrame::OnDrawAND)
EVT_MENU(1008, MyFrame::OnUndo)
EVT_MENU(1009, MyFrame::Onlianxian)
EVT_MENU(1010, MyFrame::OnDraw0)
EVT_MENU(1011, MyFrame::OnDraw1)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
EVT_PAINT(MyFrame::OnPaint)
EVT_LEFT_DOWN(MyFrame::OnMouseDown)
EVT_LEFT_UP(MyFrame::OnMouseUp)
EVT_MOTION(MyFrame::OnMouseMove)

//EVT_MENU(Show_Shaped, MyFrame::OnShowShaped)
wxEND_EVENT_TABLE()
#pragma endregion

#pragma region ShapedFrameEvent
BEGIN_EVENT_TABLE(ShapedFrame, wxFrame)
EVT_MOTION(ShapedFrame::OnMouseMove)
EVT_PAINT(ShapedFrame::OnPaint)
EVT_LEFT_DOWN(ShapedFrame::OnLeftDown)
EVT_LEFT_UP(ShapedFrame::OnLeftUp)
EVT_RIGHT_UP(ShapedFrame::OnExit)
END_EVENT_TABLE()
#pragma endregion

#pragma region SizerPanelEvent
wxBEGIN_EVENT_TABLE(SizerPanel, wxPanel)
END_EVENT_TABLE()
#pragma endregion



#pragma endregion

// Application implementation
wxIMPLEMENT_APP(MyApp);

//tittle����
bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("CAD");
    wxInitAllImageHandlers();
    frame->Show(true);
    return true;
}

#pragma region ��ͬFrame��Ӧ����ʵ��

#pragma region MyFrame�йط���ʵ��

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title), m_canvas(1200, 800), m_drawing(false), m_drawOR(false), m_drawAND(false), m_drawNOT(false) {

    wxToolBar* toolbar = CreateToolBar();
    toolbar->AddTool(1001, "�����ļ�", wxArtProvider::GetBitmap(wxART_FILE_OPEN));
    toolbar->AddTool(1002, "����", wxArtProvider::GetBitmap(wxART_FILE_SAVE));
    toolbar->AddTool(1003, "������PDF", wxArtProvider::GetBitmap(wxART_FILE_SAVE_AS));
    toolbar->AddTool(1004, "���", wxArtProvider::GetBitmap(wxART_DELETE));
    toolbar->AddTool(1005, "������", wxArtProvider::GetBitmap(wxART_TIP));
    toolbar->AddTool(1006, "������", wxArtProvider::GetBitmap(wxART_GO_DOWN));
    toolbar->AddTool(1007, "������", wxArtProvider::GetBitmap(wxART_TIP));
    toolbar->AddTool(1008, "����", wxArtProvider::GetBitmap(wxART_UNDO));
    toolbar->AddTool(1009, "����", wxArtProvider::GetBitmap(wxART_TIP));
    toolbar->AddTool(1010, "��0", wxArtProvider::GetBitmap(wxART_TIP));
    toolbar->AddTool(1011, "��1", wxArtProvider::GetBitmap(wxART_TIP));
    toolbar->Realize();

    wxMenu* menuFile = new wxMenu;
    menuFile->Append(1001, "�����ļ�\tCtrl-I", "�����ļ�");
    menuFile->Append(1002, "����\tCtrl-S", "���������Ŀ");
    menuFile->Append(1003, "������PDF\tCtrl-E", "���ļ�������PDF��ʽ");
    menuFile->Append(1004, "���\tCtrl-L", "�����������");
    menuFile->Append(1005, "������\tCtrl-R", "�����Ż��ڻ�����");
    menuFile->Append(1006, "������\tCtrl-C", "�����Ż��ڻ�����");
    menuFile->Append(1007, "������\tCtrl-L", "�����Ż��ڻ�����");
    menuFile->Append(1008, "����\tCtrl-Z", "������һ���������");
    menuFile->Append(1009, "����\tCtrl-K", "��Ԫ��֮������");
    menuFile->Append(1010, "��0\tCtrl-O", "��0���ڻ�����");
    menuFile->Append(1011, "��1\tCtrl-N", "��1���ڻ�����");
    menuFile->Append(wxID_EXIT, "Exit\tCtrl-Q", "�رճ���");

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT, "About\tCtrl-A", "Information about this application");

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "File");
    menuBar->Append(menuHelp, "Help");
    SetMenuBar(menuBar);


#pragma region ���������
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    // ���������
    wxPanel* sidePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 600));
    wxBoxSizer* sideSizer = new wxBoxSizer(wxVERTICAL);
    SizerPanel* sizerPanel = new SizerPanel(sideSizer, sidePanel, this);
    sidePanel->SetSizer(sideSizer);

    // �����������Ҫ���ݲ�������
    mainSizer->Add(sidePanel, 0, wxEXPAND);

    SetSizerAndFit(mainSizer);

    SetSize(1000, 1000);
#pragma endregion
}

void MyFrame::OnImportCAD(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, "Open PNG File", "", "",
        "PNG files (*.png)|*.png",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_OK) {
        wxString filePath = openFileDialog.GetPath();
        wxImage image(filePath);
        wxMessageBox("Imported PNG file: " + filePath, "Info", wxOK | wxICON_INFORMATION);
        if (image.IsOk())
        {
            // ��wxImageת��ΪwxBitmap
            wxBitmap bitmap(image);
            m_canvas = bitmap; // ����m_canvas��wxBitmap���ͣ��洢��������

            // ˢ�»�������ʾ�µ�ͼ��
            Refresh();
        }
        else
        {
            wxMessageBox("Failed to load the PNG file.", "Error", wxOK | wxICON_ERROR);
        }
    }
}

void MyFrame::OnSave(wxCommandEvent& event) {
    wxFileDialog saveFileDialog(this, "Save File", "", "",
        "PNG files (*.png)|*.png",
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_OK) {
        wxString filePath = saveFileDialog.GetPath();
        SaveCanvasAsPNG(filePath);
        wxMessageBox("Saved project to: " + filePath, "Info", wxOK | wxICON_INFORMATION);
    }
}

void MyFrame::OnExportPDF(wxCommandEvent& event) {
    wxFileDialog saveFileDialog(this, "Export to PDF", "", "",
        "PDF files (*.pdf)|*.pdf",
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_OK) {
        wxString filePath = saveFileDialog.GetPath();
        wxMessageBox("Exported to PDF: " + filePath, "Info", wxOK | wxICON_INFORMATION);
    }
}

void MyFrame::OnClearCanvas(wxCommandEvent& event) {
    m_shapes.clear();
    wxMemoryDC dc(m_canvas);
    dc.SetBackground(wxBrush(GetBackgroundColour()));
    dc.Clear();

    Refresh();
    wxMessageBox("Canvas cleared!", "Info", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnDrawNOT(wxCommandEvent& event) {
    m_drawNOT = true;
    m_drawOR = false;
    m_drawAND = false;
    m_lianxian = false;
    m_draw0 = false;
    m_draw1 = false;
    wxMessageBox("�ڻ����ϵ�����ɻ������š�", "������", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnDrawOR(wxCommandEvent& event) {
    m_drawOR = true;
    m_drawAND = false;
    m_drawNOT = false;
    m_lianxian = false;
    m_draw0 = false;
    m_draw1 = false;
    wxMessageBox("�ڻ����ϵ�����ɻ������š�", "������", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnDrawAND(wxCommandEvent& event) {
    m_drawAND = true;
    m_drawOR = false;
    m_drawNOT = false;
    m_lianxian = false;
    m_draw0 = false;
    m_draw1 = false;
    wxMessageBox("�ڻ����ϵ�����ɻ������š�", "������", wxOK | wxICON_INFORMATION);
}

void MyFrame::Onlianxian(wxCommandEvent& event) {
    m_drawAND = false;
    m_drawOR = false;
    m_drawNOT = false;
    m_lianxian = true;
    m_draw0 = false;
    m_draw1 = false;
    wxMessageBox("���������㣬�ٴε�������յ㣬��������һ����", "����", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnDraw0(wxCommandEvent& event)
{
    m_drawAND = false;
    m_drawOR = false;
    m_drawNOT = false;
    m_lianxian = false;
    m_draw0 = true;
    m_draw1 = false;
    wxMessageBox("�ڻ����ϵ�����ɻ��� 0��", "�� 0", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnDraw1(wxCommandEvent& event)
{
    m_drawAND = false;
    m_drawOR = false;
    m_drawNOT = false;
    m_lianxian = false;
    m_draw0 = false;
    m_draw1 = true;
    wxMessageBox("�ڻ����ϵ�����ɻ��� 1��", "�� 1", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnUndo(wxCommandEvent& event) {
    if (!m_shapes.empty()) {
        m_shapes.pop_back();
        UpdateCanvas();
    }
    else {
        wxMessageBox("û��ͼ�ο��Գ���", "����", wxOK | wxICON_INFORMATION);
    }
}

void MyFrame::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);
    dc.DrawBitmap(m_canvas, 0, 0, true);
}

void MyFrame::OnMouseDown(wxMouseEvent& event) {
    if (event.LeftIsDown()) {
        m_startPoint = event.GetPosition();
        m_drawing = true;
    }
}

void MyFrame::OnMouseMove(wxMouseEvent& event) {
    if (m_drawing) {
        m_endPoint = event.GetPosition();
        UpdateCanvas(); // Update the canvas with the current shape
    }
}

void MyFrame::OnMouseUp(wxMouseEvent& event) {
    if (m_drawing) {
        m_drawing = false;

        // ���뵽����
       // m_startPoint.x = (m_startPoint.x / GRID_SIZE) * GRID_SIZE;
        //m_startPoint.y = (m_startPoint.y / GRID_SIZE) * GRID_SIZE;
        //m_endPoint.x = (m_endPoint.x / GRID_SIZE) * GRID_SIZE;
        //m_endPoint.y = (m_endPoint.y / GRID_SIZE) * GRID_SIZE;

        Shape shape = { m_startPoint, m_endPoint, m_drawOR, m_drawNOT, m_lianxian , m_draw0, m_draw1 };

        if (m_drawAND) {
            shape.isOR = false;
            shape.isNOT = false;
            shape.islianxian = false;
            shape.is0 = false;
            shape.is1 = false;
        }

        m_shapes.push_back(shape);
        UpdateCanvas(); // Finalize the drawing
    }
}

void MyFrame::UpdateCanvas() {
    wxMemoryDC dc(m_canvas);
    dc.SetBackground(wxBrush(GetBackgroundColour()));
    dc.Clear();
    // ��������
    DrawGrid(dc);

    // Draw previous shapes
    DrawShapes(dc);

    // Draw current temporary shape
    if (m_drawing) {
        dc.SetBrush(wxBrush(wxColor(0, 0, 255, 128))); // semi-transparent color
        dc.SetPen(wxPen(wxColor(0, 0, 255), 2));

        if (m_drawOR) {
            int radius = static_cast<int>(sqrt(pow(m_endPoint.x - m_startPoint.x, 2) + pow(m_endPoint.y - m_startPoint.y, 2)));
            dc.DrawCircle(m_startPoint.x, m_startPoint.y, radius);
        }
        else if (m_lianxian) {
            dc.DrawLine(m_startPoint.x, m_startPoint.y + 35, m_endPoint.x, m_endPoint.y + 35);
        }
        else if (m_drawAND) {
            dc.DrawSpline(m_startPoint.x, m_startPoint.y, m_startPoint.x + 50, m_startPoint.y + 50, m_startPoint.x, m_startPoint.y + 100);
        }
        else if (m_drawNOT) {
            dc.DrawRectangle(m_startPoint.x, m_startPoint.y,
                m_endPoint.x - m_startPoint.x,
                m_endPoint.y - m_startPoint.y);
        }
    }

    Refresh();
}

void MyFrame::DrawShapes(wxMemoryDC& dc) {
    if (m_canvas.IsOk()) {
        dc.DrawBitmap(m_canvas, 0, 0, true);
    }

    dc.SetBrush(wxBrush(wxColor(0, 0, 0), wxBRUSHSTYLE_TRANSPARENT));
    dc.SetPen(wxPen(wxColor(0, 0, 255), 2));

    for (const auto& shape : m_shapes) {
        if (shape.isOR) {
            dc.DrawArc(shape.start.x, shape.start.y + 57, shape.start.x, shape.start.y + 7, shape.start.x - 10, shape.start.y + 32);
            dc.DrawLine(shape.start.x, shape.start.y + 57, shape.start.x + 60, shape.start.y + 57);
            dc.DrawLine(shape.start.x, shape.start.y + 7, shape.start.x + 60, shape.start.y + 7);
            dc.DrawArc(shape.start.x + 60, shape.start.y + 57, shape.start.x + 60, shape.start.y + 7, shape.start.x + 50, shape.start.y + 32);
            dc.SetPen(wxPen(wxColor(255, 0, 0), 2));
            dc.DrawCircle(shape.start.x + 74, shape.start.y + 32, 2);
            dc.DrawCircle(shape.start.x + 14, shape.start.y + 42, 2);
            dc.DrawCircle(shape.start.x + 14, shape.start.y + 22, 2);
            dc.SetPen(wxPen(wxColor(0, 0, 255), 2));
        }
        else if (shape.isNOT) {

            dc.DrawLine(shape.start.x, shape.start.y + 7, shape.start.x + 50, shape.start.y + 32);
            dc.DrawLine(shape.start.x, shape.start.y + 57, shape.start.x + 50, shape.start.y + 32);
            dc.DrawLine(shape.start.x, shape.start.y + 7, shape.start.x, shape.start.y + 57);
            dc.DrawCircle(shape.start.x + 55, shape.start.y + 32, 5);
            dc.SetPen(wxPen(wxColor(255, 0, 0), 2));
            dc.DrawCircle(shape.start.x + 60, shape.start.y + 32, 2);
            dc.DrawCircle(shape.start.x, shape.start.y + 42, 2);
            dc.DrawCircle(shape.start.x, shape.start.y + 22, 2);
            dc.SetPen(wxPen(wxColor(0, 0, 255), 2));

        }
        else if (shape.islianxian) {
            dc.DrawLine(shape.start.x, shape.start.y + 35, shape.end.x, shape.end.y + 35);
        }
        else if (shape.is0) {
            dc.SetPen(wxPen(wxColor(255, 0, 0), 2));
            dc.DrawCircle(shape.start.x, shape.start.y + 35, 10);
            dc.DrawText('0', shape.start.x - 2.5, shape.start.y + 27);
            dc.DrawCircle(shape.start.x + 10, shape.start.y + 35, 2);
            dc.SetPen(wxPen(wxColor(0, 0, 255), 2));
            dc.DrawLine(shape.start.x - 10, shape.start.y + 25, shape.start.x + 10, shape.start.y + 25);
            dc.DrawLine(shape.start.x - 10, shape.start.y + 45, shape.start.x + 10, shape.start.y + 45);
            dc.DrawLine(shape.start.x - 10, shape.start.y + 25, shape.start.x - 10, shape.start.y + 45);
            dc.DrawLine(shape.start.x + 10, shape.start.y + 25, shape.start.x + 10, shape.start.y + 45);
        }
        else if (shape.is1) {
            dc.SetPen(wxPen(wxColor(255, 0, 0), 2));
            dc.DrawCircle(shape.start.x, shape.start.y + 35, 10);
            dc.DrawText('1', shape.start.x - 2.5, shape.start.y + 27);
            dc.DrawCircle(shape.start.x + 10, shape.start.y + 35, 2);
            dc.SetPen(wxPen(wxColor(0, 0, 255), 2));
            dc.DrawLine(shape.start.x - 10, shape.start.y + 25, shape.start.x + 10, shape.start.y + 25);
            dc.DrawLine(shape.start.x - 10, shape.start.y + 45, shape.start.x + 10, shape.start.y + 45);
            dc.DrawLine(shape.start.x - 10, shape.start.y + 25, shape.start.x - 10, shape.start.y + 45);
            dc.DrawLine(shape.start.x + 10, shape.start.y + 25, shape.start.x + 10, shape.start.y + 45);

        }
        else {

            dc.DrawLine(shape.start.x, shape.start.y + 10, shape.start.x, shape.start.y + 60);
            dc.DrawLine(shape.start.x, shape.start.y + 10, shape.start.x + 60, shape.start.y + 10);
            dc.DrawLine(shape.start.x, shape.start.y + 60, shape.start.x + 60, shape.start.y + 60);
            dc.DrawArc(shape.start.x + 60, shape.start.y + 60, shape.start.x + 60, shape.start.y + 10, shape.start.x + 50, shape.start.y + 35);
            dc.SetPen(wxPen(wxColor(255, 0, 0), 2));
            dc.DrawCircle(shape.start.x + 74, shape.start.y + 35, 2);
            dc.DrawCircle(shape.start.x, shape.start.y + 45, 2);
            dc.DrawCircle(shape.start.x, shape.start.y + 25, 2);
            dc.SetPen(wxPen(wxColor(0, 0, 255), 2));
        }
    }
}

void MyFrame::DrawGrid(wxMemoryDC& dc) {
    dc.SetPen(wxPen(wxColor(200, 200, 200), 1)); // ǳ��ɫ������

    for (int x = 0; x < m_canvas.GetWidth(); x += GRID_SIZE) {
        dc.DrawLine(x, 0, x, m_canvas.GetHeight());
    }

    for (int y = 0; y < m_canvas.GetHeight(); y += GRID_SIZE) {
        dc.DrawLine(0, y, m_canvas.GetWidth(), y);
    }
}

void MyFrame::SaveCanvasAsPNG(const wxString& filename)
{
    // ȷ��m_canvas�Ѿ����������л��Ƶ�����
    m_canvas.SaveFile(filename, wxBITMAP_TYPE_PNG);
}



void MyFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is an industrial design application for CAD management.", "About", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnQuit(wxCommandEvent& event) {
    Close(true);
}


//void MyFrame::OnShowShaped(wxCommandEvent& event)
//{
//    ShapedFrame* frame = new ShapedFrame(this);
//    frame->Show();
//}
#pragma endregion

#pragma region ShapedFrame�йط���ʵ��
ShapedFrame::ShapedFrame(wxFrame* parent) :wxFrame(NULL, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, 300), wxFRAME_SHAPED | wxSIMPLE_BORDER | wxFRAME_NO_TASKBAR | wxSTAY_ON_TOP)
{
    /*wxAnimationCtrl* an = new wxAnimationCtrl(this, wxID_ANY, wxAnimation(wxT("ddear.gif"), wxANIMATION_TYPE_ANY), wxDefaultPosition, wxDefaultSize, 2097152L, wxAnimationCtrlNameStr);
    an->Play();*/
    m_shapeKind = Shape_Star;
    m_bitmap = wxBitmap("star.png", wxBITMAP_TYPE_PNG);
    SetSize(wxSize(m_bitmap.GetWidth(), m_bitmap.GetHeight()));
    SetToolTip("Right Click To Close");
    SetWindowShape();
}

void ShapedFrame::SetWindowShape()
{
    switch (m_shapeKind)
    {
    case Shape_None:
        SetShape(wxRegion());
        break;

    case Shape_Star:
        SetShape(wxRegion(m_bitmap, *wxWHITE));
    }

}

void ShapedFrame::OnLeftDown(wxMouseEvent& evt)
{
    CaptureMouse();
    wxPoint pos = ClientToScreen(evt.GetPosition());
    wxPoint origin = GetPosition();
    int dx = pos.x - origin.x;
    int dy = pos.y - origin.y;
    m_delta = wxPoint(dx, dy);
}

void ShapedFrame::OnLeftUp(wxMouseEvent& WXUNUSED(evt))
{
    if (HasCapture())
    {
        ReleaseMouse();
    }
}

void ShapedFrame::OnMouseMove(wxMouseEvent& event)
{
    wxPoint pt = event.GetPosition();
    if (event.Dragging() && event.LeftIsDown())
    {
        wxPoint pos = ClientToScreen(pt);
        Move(wxPoint(pos.x - m_delta.x, pos.y - m_delta.y));
    }
}


void ShapedFrame::OnExit(wxMouseEvent& event)
{
    Close();
}

void ShapedFrame::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    dc.DrawBitmap(m_bitmap, 0, 0, true);
}
#pragma endregion

#pragma region SizerFrame�йط���ʵ��
SizerPanel::SizerPanel(wxBoxSizer* Sizer, wxPanel* Panel, wxFrame* parent)
    :wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
    wxFrame* parentFrame = parent;
    // �ڲ��������Ӱ�ť
    wxButton* button1 = new wxButton(Panel, wxID_ANY, "AND");
    button1->Bind(wxEVT_BUTTON, [this, parentFrame](wxCommandEvent& event) {
        ButtonAnd(event, parentFrame); });
    Sizer->Add(button1, 0, wxEXPAND | wxALL, 5);

    wxButton* button2 = new wxButton(Panel, wxID_ANY, "Or");
    button2->Bind(wxEVT_BUTTON, [this, parentFrame](wxCommandEvent& event) {
        ButtonOr(event, parentFrame); });
    Sizer->Add(button2, 0, wxEXPAND | wxALL, 5);

    wxButton* button3 = new wxButton(Panel, wxID_ANY, "Not");
    button3->Bind(wxEVT_BUTTON, [this, parentFrame](wxCommandEvent& event) {
        ButtonNot(event, parentFrame); });
    Sizer->Add(button3, 0, wxEXPAND | wxALL, 5);
}

void SizerPanel::ButtonAnd(wxCommandEvent& event, wxFrame* parentFrame)
{
    /*ShapedFrame* frame = new ShapedFrame(parentFrame);
    frame->m_bitmap = wxBitmap("and.png", wxBITMAP_TYPE_PNG);
    frame->SetShape(wxRegion(frame->m_bitmap, *wxWHITE));
    frame->Show();*/
}

void SizerPanel::ButtonOr(wxCommandEvent& event, wxFrame* parentFrame)
{
    /*ShapedFrame* frame = new ShapedFrame(parentFrame);
    frame->m_bitmap = wxBitmap("or.png", wxBITMAP_TYPE_PNG);
    frame->SetShape(wxRegion(frame->m_bitmap, *wxWHITE));
    frame->Show();*/
}

void SizerPanel::ButtonNot(wxCommandEvent& event, wxFrame* parentFrame)
{
    /*ShapedFrame* frame = new ShapedFrame(parentFrame);
    frame->m_bitmap = wxBitmap("not.png", wxBITMAP_TYPE_PNG);'
    frame->SetShape(wxRegion(frame->m_bitmap, *wxWHITE));
    frame->Show();*/
}
#pragma endregion

#pragma endregion