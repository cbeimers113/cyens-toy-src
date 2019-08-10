#include "QuickOption.h"
#include "GameModel.h"

class SandEffectOption : public QuickOption
{
public:
	SandEffectOption(GameModel * m) :
		QuickOption("P", "Sand effect", m, Toggle)
	{

	}
	virtual bool GetToggle()
	{
		return m->GetSimulation()->pretty_powder;
	}
	virtual void perform()
	{
		m->GetSimulation()->pretty_powder = !m->GetSimulation()->pretty_powder;
	}
};

class DrawGravOption : public QuickOption
{
public:
	DrawGravOption(GameModel * m) :
		QuickOption("G", "Draw gravity field \bg(ctrl+g)", m, Toggle)
	{

	}
	virtual bool GetToggle()
	{
		return m->GetGravityGrid();
	}
	virtual void perform()
	{
		m->ShowGravityGrid(!m->GetGravityGrid());
	}
};

class DecorationsOption : public QuickOption
{
public:
	DecorationsOption(GameModel * m) :
		QuickOption("D", "Draw decorations \bg(ctrl+b)", m, Toggle)
	{

	}
	virtual bool GetToggle()
	{
		return m->GetDecoration();
	}
	virtual void perform()
	{
		m->SetDecoration(!m->GetDecoration());
	}
};

class NGravityOption : public QuickOption
{
public:
	NGravityOption(GameModel * m) :
		QuickOption("N", "Newtonian Gravity \bg(n)", m, Toggle)
	{

	}
	virtual bool GetToggle()
	{
		return m->GetNewtonianGrvity();
	}
	virtual void perform()
	{
		m->SetNewtonianGravity(!m->GetNewtonianGrvity());
	}
};

class AHeatOption : public QuickOption
{
public:
	AHeatOption(GameModel * m) :
		QuickOption("A", "Ambient heat \bg(u)", m, Toggle)
	{

	}
	virtual bool GetToggle()
	{
		return m->GetAHeatEnable();
	}
	virtual void perform()
	{
		m->SetAHeatEnable(!m->GetAHeatEnable());
	}
};

class ConsoleShowOption : public QuickOption
{
	GameController * c;
public:
	ConsoleShowOption(GameModel * m, GameController * c_) :
		QuickOption("C", "Show Console \bg(~)", m, Toggle)
	{
		c = c_;
	}
	virtual bool GetToggle()
	{
		return 0;
	}
	virtual void perform()
	{
		c->ShowConsole();
	}
};

class InfoscreenOption : public QuickOption
{
	GameController *c;
public:
	InfoscreenOption(GameModel *m) :
		QuickOption("I", "[Not Implemented] Show Info Screen \bg(ctrl+w)", m, Toggle)
	{

	}
	virtual bool GetToggle()
	{
		return m->GetInfoscreenEnable();
	}
	virtual void perform()
	{
		m->SetInfoscreenEnable(!m->GetInfoscreenEnable());
	}
};

class TimeDilationOption : public QuickOption
{
	GameController *c;
public:
	TimeDilationOption(GameModel *m) :
		QuickOption("T", "Toggle Time Dilation \bg(t)", m, Toggle)
	{

	}
	virtual bool GetToggle()
	{
		return m->GetTimeDilationEnable();
	}
	virtual void perform()
	{
		m->SetTimeDilationEnable(!m->GetTimeDilationEnable());
	}
};

class CompressibleGasesOption : public QuickOption
{
	GameController *c;
public:
	CompressibleGasesOption(GameModel *m) :
		QuickOption("O", "Toggle Compressible Gases \bg(o)", m, Toggle)
	{

	}
	virtual bool GetToggle()
	{
		return m->GetCompressibleGasesEnable();
	}
	virtual void perform()
	{
		m->SetCompressibleGasesEnable(!m->GetCompressibleGasesEnable());
	}
};