/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "DisplayHelloTransformIOExport.h"

#include "itkDisplayHelloTransformIOFactory.h"
#include "itkCreateObjectFunction.h"
#include "itkDisplayHelloTransformIO.h"
#include "itkVersion.h"

/**
 * Routine that is called when the shared library is loaded by
 * itk::ObjectFactoryBase::LoadDynamicFactories().
 *
 * itkLoad() is C (not C++) function.
 */
extern "C" {
  DisplayHelloTransformIO_EXPORT itk::ObjectFactoryBase* itkLoad();
}


itk::ObjectFactoryBase* itkLoad()
{
  static itk::DisplayHelloTransformIOFactory::Pointer f
    = itk::DisplayHelloTransformIOFactory::New();
  std::cout << DISPLAYHELLO_TransformIO_FACTORY_NAME << std::endl;
  return f;
}

namespace itk
{
void DisplayHelloTransformIOFactory::PrintSelf(std::ostream &, Indent) const
{}

DisplayHelloTransformIOFactory::DisplayHelloTransformIOFactory()
{
  this->RegisterOverride( "itkTransformIOBaseTemplate",
                          "itkDisplayHelloTransformIO",
                          "DisplayHello Transform float IO",
                          1,
                          CreateObjectFunction< DisplayHelloTransformIOTemplate< float > >::New() );
  this->RegisterOverride( "itkTransformIOBaseTemplate",
                          "itkDisplayHelloTransformIO",
                          "DisplayHello Transform double IO",
                          1,
                          CreateObjectFunction< DisplayHelloTransformIOTemplate< double > >::New() );
}

DisplayHelloTransformIOFactory::~DisplayHelloTransformIOFactory()
{}

const char *
DisplayHelloTransformIOFactory::GetITKSourceVersion(void) const
{
  return ITK_SOURCE_VERSION;
}

const char *
DisplayHelloTransformIOFactory::GetDescription() const
{
  return "DisplayHello TransformIO Factory, displays its name when registered";
}

} // end namespace itk
