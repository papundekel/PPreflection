#pragma once

namespace visitors
{
	struct animal_visitor;
}

namespace animals
{
	extern int value;

	struct animal
	{
		virtual const char* name() const noexcept = 0;
		virtual void accept(visitors::animal_visitor& visitor) = 0;
		virtual ~animal() = default;
	};

	struct ape final
		: public animal
	{
		const char* name() const noexcept override final;
		void accept(visitors::animal_visitor& visitor) override final;
	};

	struct bat final
		: public animal
	{
		const char* name() const noexcept override final;
		void accept(visitors::animal_visitor& visitor) override final;
	};

	struct cat final
		: public animal
	{
		const char* name() const noexcept override final;
		void accept(visitors::animal_visitor& visitor) override final;
	};

	struct dog final
		: public animal
	{
		const char* name() const noexcept override final;
		void accept(visitors::animal_visitor& visitor) override final;
	};

	struct elk final
		: public animal
	{
		const char* name() const noexcept override final;
		void accept(visitors::animal_visitor& visitor) override final;
	};
}

namespace visitors
{
	struct animal_visitor
	{
		virtual void visit(animals::ape& ape) = 0;
		virtual void visit(animals::bat& bat) = 0;
		virtual void visit(animals::cat& cat) = 0;
		virtual void visit(animals::dog& dog) = 0;
		virtual void visit(animals::elk& elk) = 0;
	};
}
