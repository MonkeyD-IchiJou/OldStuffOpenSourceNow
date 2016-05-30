-- vec3 class --

vec3 = {

	x = 0.0, 
	y = 0.0, 
	z = 0.0,

	-- metatable
	mt = {},

	-- set variable to zero
	SetZero = function(self)
		self.x = 0.0
		self.y = 0.0
		self.z = 0.0
	end,

	-- lenght of this vector
	Length = function(self)
		return math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)
	end,

	-- lenght square 
	LengthSquare = function(self)
		return self.x * self.x + self.y * self.y + self.z * self.z
	end,

	-- dot product
	Dot = function(self, rhs)
		return (self.x * rhs.x) + (self.y * rhs.y) + (self.z * rhs.z)
	end,

	-- cross product
	Cross = function(self, rhs)
		local temp = vec3.New()

		temp.x = self.y * rhs.z - self.z * rhs.y
		temp.y = self.z * rhs.x - self.x * rhs.z
		temp.z = self.x * rhs.y - self.y * rhs.x

		return temp
	end,

	-- normalised
	Normalized = function(self)

		local temp = vec3.New()

		d = self:Length();

		if (d <= 0.0 and -d <= 0.0) then
			-- do nothing
		else
			temp.x = self.x / d
			temp.y = self.y / d
			temp.z = self.z / d
		end

		return temp;

	end,

	-- normalise
	Normalize = function(self)

		d = self:Length();

		if (d <= 0.0 and -d <= 0.0) then
			self:SetZero()
		else
			self.x = self.x / d
			self.y = self.y / d
			self.z = self.z / d
		end

	end,

	-- set up
	Set = function(self, nx, ny, nz)
		self.x = nx
		self.y = ny
		self.z = nz
	end,


	-- oop new
	New = function()

		local vec = {}

		-- operator overload is metatable
		setmetatable(vec, vec3.mt)

		-- copy all the variables into new table 
		for k, v in pairs(vec3) do
			vec[k] = v
		end

		return vec
	end,
}



-- metatable implementation --

-- operator +
vec3.mt.__add = function(v1, v2)

	local vec = vec3.New()

	if type(v2) == "number" then
		vec.x = v1.x + v2
		vec.y = v1.y + v2
		vec.z = v1.z + v2
	else
		vec.x = v1.x + v2.x
		vec.y = v1.y + v2.y
		vec.z = v1.z + v2.z
	end

	return vec

end


-- operator -
vec3.mt.__sub = function(v1, v2)

	local vec = vec3.New()

	if type(v2) == "number" then
		vec.x = v1.x - v2
		vec.y = v1.y - v2
		vec.z = v1.z - v2
	else
		vec.x = v1.x - v2.x
		vec.y = v1.y - v2.y
		vec.z = v1.z - v2.z
	end

	return vec

end


-- operator *
vec3.mt.__mul = function(v1, v2)

	local vec = vec3.New()
	
	if type(v2) == "number" then
		vec.x = v1.x * v2
		vec.y = v1.y * v2
		vec.z = v1.z * v2
	else
		vec.x = v1.x * v2.x
		vec.y = v1.y * v2.y
		vec.z = v1.z * v2.z
	end

	return vec

end


-- operator /
vec3.mt.__div = function(v1, v2)

	local vec = vec3.New()

	if type(v2) == "number" then
		vec.x = v1.x / v2
		vec.y = v1.y / v2
		vec.z = v1.z / v2
	else
		vec.x = v1.x / v2.x
		vec.y = v1.y / v2.y
		vec.z = v1.z / v2.z
	end

	return vec

end



-- operator ==
vec3.mt.__eq = function(v1, v2)

	if type(v2) == "number" then
		return v1.x == v2 and v1.y == v2 and v1.z == v2
	else
		return v1.x == v2.x and v1.y == v2.y and v1.z == v2.z
	end

end



-- print 
vec3.mt.__tostring = function(vec)

	return "(" .. vec.x .. ", " .. vec.y .. ", " .. vec.z .. ")"

end