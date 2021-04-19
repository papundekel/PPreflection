#pragma once

namespace animals
{
	struct animal
	{
		virtual const char* name() const noexcept = 0;
	};

	struct ape final : public animal
	{
		const char* name() const noexcept override final;
	};

	struct bat final : public animal
	{
		const char* name() const noexcept override final;
	};

	struct cat final : public animal
	{
		const char* name() const noexcept override final;
	};

	struct dog final : public animal
	{
		const char* name() const noexcept override final;
	};

	struct elk final : public animal
	{
		const char* name() const noexcept override final;
	};
}
