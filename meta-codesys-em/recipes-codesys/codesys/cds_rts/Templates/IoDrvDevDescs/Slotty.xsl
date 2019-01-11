<?xml version="1.0" encoding="ISO-8859-1"?>
<!--
 | 
 -->

<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:ts="http://www.3s-software.com/schemas/TargetSettings-0.1.xsd" xmlns:xs="http://www.w3.org/2001/XMLSchema">
<xsl:output indent="yes"/>


  <!-- These are the arguments that have to be specified on the commandline -->
  <xsl:param name="Input" as="xs:string" required="yes"/>
  <xsl:param name="ModuleID" as="xs:integer" required="no">1700</xsl:param>				
  <xsl:param name="ModuleType" as="xs:integer" required="no">40100</xsl:param>

  <xsl:template match="/">
    <xsl:apply-templates/>
  </xsl:template>

  <xsl:template match="*">
    <xsl:choose>

      <xsl:when test="name() = 'Device'">
        <xsl:element name="{name()}">

          <xsl:copy-of select="@*"/>
          <!-- [recursion] -->
          <xsl:apply-templates/>

          <xsl:for-each select="document($Input)/DeviceDescription/Device/*">
            <xsl:choose>
              <xsl:when test="name() = 'Slots'">
                <xsl:element name="Connector">
                  <xsl:attribute name="ConnectorId"><xsl:value-of select="1 + position()"/></xsl:attribute>
                  <xsl:attribute name="HostPath">-1</xsl:attribute>
                  <xsl:attribute name="interface"><xsl:value-of select="@interface"/></xsl:attribute>
                  <xsl:attribute name="moduleType"><xsl:value-of select="$ModuleType + position()"/></xsl:attribute>
                  <xsl:attribute name="role">parent</xsl:attribute>
                  <xsl:element name="Slot">
                    <xsl:attribute name="allowEmpty">false</xsl:attribute>
                    <xsl:attribute name="count"><xsl:value-of select="@num"/></xsl:attribute>
                  </xsl:element>
                </xsl:element>
              </xsl:when>
            </xsl:choose>
          </xsl:for-each>
        </xsl:element>
      </xsl:when>


      <xsl:when test="name() = 'DeviceDescription'">
        <xsl:element name="{name()}">
          <xsl:copy-of select="@*"/>
          <!-- [recursion] -->
          <xsl:apply-templates/>
          
          <xsl:element name="Modules">
            <xsl:for-each select="document($Input)/DeviceDescription/Modules/Module">
              <xsl:element name="Module">
                <xsl:element name="ModuleId">
                  <xsl:value-of select="$ModuleID + position()"/>
                </xsl:element>
                
                <xsl:copy-of select="document(@template)/Module/DeviceInfo"/>
                <xsl:element name="Connector">
                  <xsl:attribute name="ConnectorId"><xsl:value-of select="1 + position()"/></xsl:attribute>
                  <xsl:attribute name="HostPath">-1</xsl:attribute>
                  <xsl:attribute name="interface"><xsl:value-of select="@interface"/></xsl:attribute>
                  <xsl:attribute name="moduleType"><xsl:value-of select="$ModuleType + 1000 + position()"/></xsl:attribute>
                  <xsl:attribute name="role">child</xsl:attribute>
                  <xsl:copy-of select="document(@template)/Module/Connector/*"/>
                </xsl:element>
              </xsl:element>
            </xsl:for-each>
          </xsl:element>
        </xsl:element>
      </xsl:when>

      <!-- Just copy the tags recursively -->
      <xsl:otherwise>
        <xsl:element name="{name()}">
          <xsl:copy-of select="@*"/>
          <!-- [recursion] -->
          <xsl:apply-templates/>
        </xsl:element>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>



</xsl:stylesheet>

